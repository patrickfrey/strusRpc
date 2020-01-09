/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "rpcSerializer.hpp"
#include "hexdump.h"
#include "private/internationalization.hpp"
#include "strus/base/crc32.hpp"
#include "rpcProtocolDefines.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include "strus/base/stdint.h"

using namespace strus;

#undef STRUS_LOWLEVEL_DEBUG
#ifndef STRUS_RPC_PROTOCOL_WITH_TYPED_ATOMS
#error Missing include of rpcProtocolDefines.hpp
#endif

namespace {

#undef STRUS_ALTERNATIVE_CHECK_SUM
#ifdef STRUS_ALTERNATIVE_CHECK_SUM

enum AlternativeCheckProperties
{
	NofNonAscii,
	NofSpaces,
	NofAscii,
	NofNull
};

uint32_t calcAlternativeCheckSum( const char* ptr, std::size_t ptrsize)
{
	unsigned char xx[4] = {0,0,0,0};
	char const* si = ptr;
	char const* se = ptr + ptrsize;

	for (si=ptr; si != se; ++si)
	{
		if ((unsigned char)*si > 127) xx[ NofNonAscii] += 1;
		if ((unsigned char)*si <= 32 && (unsigned char)*si > 0) xx[ NofSpaces] += 1;
		if ((unsigned char)*si > 32 && (unsigned char)*si <= 127) xx[ NofAscii] += 1;
		if ((unsigned char)*si == 0) xx[ NofNull] += 1;
	}
	return ((unsigned int)xx[3] << 24) + ((unsigned int)xx[2] << 16) + ((unsigned int)xx[1] << 8) + xx[0];
}

bool checkAlternativeCheckSum( uint32_t aa, uint32_t bb)
{
	bool rt = true;
	unsigned char aaval[4];
	unsigned char bbval[4];
	aaval[3] = (aa >> 24) & 0xff;
	aaval[2] = (aa >> 16) & 0xff;
	aaval[1] = (aa >>  8) & 0xff;
	aaval[0] = (aa >>  0) & 0xff;

	bbval[3] = (bb >> 24) & 0xff;
	bbval[2] = (bb >> 16) & 0xff;
	bbval[1] = (bb >>  8) & 0xff;
	bbval[0] = (bb >>  0) & 0xff;

	if (aaval[NofNonAscii] != bbval[NofNonAscii])
	{
		std::cerr << "Checksums differ in number of non ascii characters " << (unsigned int)aaval[NofNonAscii] << " != " << (unsigned int)bbval[NofNonAscii] << std::endl;
		rt = false;
	}
	if (aaval[NofSpaces] != bbval[NofSpaces])
	{
		std::cerr << "Checksums differ in number of spaces " << (unsigned int)aaval[NofSpaces] << " != " << (unsigned int)bbval[NofSpaces] << std::endl;
		rt = false;
	}
	if (aaval[NofAscii] != bbval[NofAscii])
	{
		std::cerr << "Checksums differ in number of ascii characters " << (unsigned int)aaval[NofAscii] << " != " << (unsigned int)bbval[NofAscii] << std::endl;
		rt = false;
	}
	if (aaval[NofNull] != bbval[NofNull])
	{
		std::cerr << "Checksums differ in number of null characters " << (unsigned int)aaval[NofNull] << " != " << (unsigned int)bbval[NofNull] << std::endl;
		rt = false;
	}
	return rt;
}
#endif

template <int>
static void pack( std::string& buf, const void* ptr);
template <int>
static void unpack( char const*&, const char*, void* ptr);

template <>
void pack<1>( std::string& buf, const void* ptr)
{
	buf.push_back( ((const char*)ptr)[0]);
}
template <>
void unpack<1>( char const*& itr, const char* end, void* ptr)
{
	if (itr+1 > end) throw std::runtime_error( _TXT("message to small to encode next byte"));
	*(char*)ptr = *itr++;
}

#ifdef UNUSED_PACK_SCALAR_16_BITS_DISABLED
template <>
void pack<2>( std::string& buf, const void* ptr)
{
	uint16_t vv = htons( *(const uint16_t*)ptr);
	buf.append( (const char*)&vv, 2);
}
template <>
void unpack<2>( char const*& itr, const char* end, void* ptr)
{
	if (itr+2 > end) throw std::runtime_error( _TXT("message to small to encode next word"));
	uint16_t val;
	std::memcpy( &val, itr, 2);
	itr += 2;
	*(uint16_t*)ptr = ntohs( val);
}
#endif

template <>
void pack<4>( std::string& buf, const void* ptr)
{
	uint32_t vv = htonl( *(const uint32_t*)ptr);
	buf.append( (const char*)&vv, 4);
}
template <>
void unpack<4>( char const*& itr, const char* end, void* ptr)
{
	if (itr+4 > end)
	{
		throw std::runtime_error( _TXT("message to small to encode next dword"));
	}
	uint32_t val;
	std::memcpy( &val, itr, 4);
	itr += 4;
	*(uint32_t*)ptr = ntohl( val);
}

template <>
void pack<8>( std::string& buf, const void* ptr)
{
	uint32_t vhi = htonl( *((const uint64_t*)ptr) >> 32);
	uint32_t vlo = htonl( *((const uint64_t*)ptr) & 0xffFFffFFUL);
	
	buf.append( (const char*)&vhi, 4);
	buf.append( (const char*)&vlo, 4);
}
template <>
void unpack<8>( char const*& itr, const char* end, void* ptr)
{
	if (itr+8 > end) throw std::runtime_error( _TXT("message to small to encode next qword"));
	uint32_t vlo;
	uint32_t vhi;
	unpack<4>( itr, end, &vhi);
	unpack<4>( itr, end, &vlo);
	*(uint64_t*)ptr = ((uint64_t)vhi << 32) + vlo;
}

template <typename SCALAR>
static void packScalar( std::string& buf, const SCALAR& val)
{
	pack<sizeof(SCALAR)>( buf, &val);
}
template <typename SCALAR>
static SCALAR unpackScalar( char const*& itr, const char* end)
{
	SCALAR val;
	unpack<sizeof(SCALAR)>( itr, end, &val);
	return val;
}
}

enum ProtocolAtomicTypes
{
	ProtocolVoid,
	ProtocolSessionId,
	ProtocolObject,
	ProtocolString,
	ProtocolCharp,
	ProtocolCharpp,
	ProtocolBuffer,
	ProtocolBufferFloat,
	ProtocolBool,
	ProtocolByte,
	ProtocolIndex,
	ProtocolGlobalCounter,
	ProtocolUint,
	ProtocolInt,
	ProtocolUint64,
	ProtocolInt64,
	ProtocolDouble,
	ProtocolFloat,
	ProtocolSize,
	ProtocolNumericVariant,
	ProtocolIndexRange
};

#if STRUS_RPC_PROTOCOL_WITH_TYPED_ATOMS
#define SET_TYPE( TP)\
	packScalar( m_content, (unsigned char)(Protocol ## TP));
#define CHECK_TYPE( TP)\
	if (unpackScalar<unsigned char>( m_itr, m_end) != (unsigned char)(Protocol ## TP))\
	{\
		throw std::runtime_error( _TXT("unpack RPC expected type " #TP));\
	}
#else
#define SET_TYPE(TP)
#define CHECK_TYPE(TP)
#endif

void RpcSerializer::packSessionId( unsigned int id_)
{
	SET_TYPE( SessionId)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packSessionId " << id_ << std::endl;
#endif
	packScalar( m_content, (uint32_t)id_);
}

void RpcSerializer::packObject( unsigned char classId_, unsigned int objId_)
{
	SET_TYPE( Object)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packObject (" << (unsigned int)classId_ << ", " << objId_ << ")" << std::endl;
#endif
	if (objId_ > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( _TXT("object id out of range"));
	packScalar( m_content, classId_);
	packScalar( m_content, (uint32_t)objId_);
}

void RpcSerializer::packString( const std::string& str)
{
	SET_TYPE( String)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packString ('" << str << "')" << std::endl;
#endif
	if (str.size() > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( _TXT("string size out of range"));
	packScalar( m_content, (uint32_t)str.size());
	m_content.append( str);
	
}

void RpcSerializer::packCharp( const char* buf)
{
	SET_TYPE( Charp)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packCharp ('" << buf << "')" << std::endl;
#endif
	if (buf) m_content.append( buf);
	m_content.push_back( '\0');
}

void RpcSerializer::packCharpp( const char** buf)
{
	SET_TYPE( Charpp)
	if (buf)
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		char const** gi = buf;
		std::cerr << "packCharpp (";
		for (int gidx=0; *gi; ++gi,++gidx)
		{
			if (gidx) std::cerr << ", ";
			std::cerr << "'" << *gi << "'";
		}
		std::cerr << ")" << std::endl;
#endif
		char const** bi = buf;
		for (; *bi; ++bi){}
		packSize( bi - buf);
		const char** be = bi;
		for (bi = buf; bi != be; ++bi)
		{
			packCharp( *bi);
		}
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cerr << "packCharpp (NULL)" << std::endl;
#endif
		packSize( 0);
	}
}

void RpcSerializer::packBuffer( const char* buf, std::size_t size)
{
	SET_TYPE( Buffer)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packBuffer('" << std::string(buf,size) << "')" << std::endl;
#endif
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( _TXT("buffer size out of range"));
	packScalar( m_content, (uint32_t)size);
	m_content.append( buf, size);
}

void RpcSerializer::packBufferFloat( const double* buf, std::size_t size)
{
	SET_TYPE( BufferFloat)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packBufferFloat( ... )" << std::endl;
#endif
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( _TXT("buffer size out of range"));
	packScalar( m_content, (uint32_t)size);
	std::size_t ii=0;
	for (ii=0; ii<size; ++ii)
	{
		packDouble( buf[ii]);
	}
}

void RpcSerializer::packBool( bool val)
{
	SET_TYPE( Bool)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packBool(" << (val?"true":"false") << ")" << std::endl;
#endif
	m_content.push_back( val?1:0);
}

void RpcSerializer::packByte( unsigned char val)
{
	SET_TYPE( Byte)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packByte (" << (unsigned int)val << ")" << std::endl;
#endif
	m_content.push_back( val);
}

void RpcSerializer::packIndex( const Index& index)
{
	SET_TYPE( Index)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packIndex (" << (unsigned int)index << ")" << std::endl;
#endif
	packScalar( m_content, index);
}

void RpcSerializer::packIndexRange( const IndexRange& val)
{
	SET_TYPE( IndexRange)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packIndexRange (" << (int)val.start() << "," << (int)val.end() << ")" << std::endl;
#endif
	packScalar( m_content, val.start());
	packScalar( m_content, val.end());
}

void RpcSerializer::packGlobalCounter( const GlobalCounter& index)
{
	SET_TYPE( GlobalCounter)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packGlobalCounter (" << (uintptr_t)index << ")" << std::endl;
#endif
	packScalar( m_content, index);
}

void RpcSerializer::packUint( unsigned int val)
{
	SET_TYPE( Uint)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packUint (" << (unsigned int)val << ")" << std::endl;
#endif
	if (val > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( _TXT("packed uint out of range"));
	packScalar( m_content, (uint32_t)val);
}

void RpcSerializer::packInt( int val)
{
	SET_TYPE( Int)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packInt (" << (signed int)val << ")" << std::endl;
#endif
	if (val > std::numeric_limits<int32_t>::max()
	||  val < std::numeric_limits<int32_t>::min()) throw std::runtime_error( _TXT("packed int out of range"));
	packScalar( m_content, (int32_t)val);
}

void RpcSerializer::packUint64( uint64_t val)
{
	SET_TYPE( Uint64)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packUint (" << (unsigned int)val << ")" << std::endl;
#endif
	packScalar( m_content, val);
}

void RpcSerializer::packInt64( int64_t val)
{
	SET_TYPE( Int64)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packInt (" << val << ")" << std::endl;
#endif
	if (val > std::numeric_limits<int64_t>::max()
	||  val < std::numeric_limits<int64_t>::min()) throw std::runtime_error( _TXT("packed int out of range"));
	packScalar( m_content, val);
}

void RpcSerializer::packFloat( float val)
{
	SET_TYPE( Float)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packFloat (" << (float)val << ")" << std::endl;
#endif
	pack<sizeof(float)>( m_content, &val);
}

void RpcSerializer::packDouble( double val)
{
	SET_TYPE( Double)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packDouble(" << (double)val << ")" << std::endl;
#endif
	pack<sizeof(double)>( m_content, &val);
}

void RpcSerializer::packSize( std::size_t size)
{
	SET_TYPE( Size)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packSize (" << (std::size_t)size << ")" << std::endl;
#endif
	if (size > std::numeric_limits<uint32_t>::max()) throw std::runtime_error( _TXT("packed size out of range"));
	packScalar( m_content, (uint32_t)size);
}

void RpcSerializer::packNumericVariant( const NumericVariant& val)
{
	SET_TYPE( NumericVariant)
	packByte( (unsigned char)val.type);
	switch (val.type)
	{
		case NumericVariant::Null: break;
		case NumericVariant::Int: packInt64( val.variant.Int); break;
		case NumericVariant::UInt: packUint64( val.variant.UInt); break;
		case NumericVariant::Float: packDouble( val.variant.Float); break;
	}
}

void RpcSerializer::packWordVector( const WordVector& val)
{
	packSize( val.size());
	WordVector::const_iterator vi = val.begin(), ve = val.end();
	for (; vi != ve; ++vi)
	{
		packFloat( *vi);
	}
}

void RpcSerializer::packStructureLink( const StructureLink& val)
{
	packBool( val.header());
	packIndex( val.structno());
	packIndex( val.index());
}

void RpcSerializer::packStructureLinkArray( const StructureLinkArray& val)
{
	int li=0, le=val.nofLinks();
	packSize( le);
	for (; li != le; ++li)
	{
		packStructureLink( val[ li]);
	}
}

void RpcSerializer::packDocumentClass( const analyzer::DocumentClass& dclass)
{
	packString( dclass.mimeType());
	packString( dclass.schema());
	packString( dclass.encoding());
}

void RpcSerializer::packAnalyzerPositionRange( const analyzer::DocumentStructure::PositionRange& val)
{
	packInt( val.start());
	packInt( val.end());
}

void RpcSerializer::packTermStatistics( const TermStatistics& stats)
{
	packGlobalCounter( stats.documentFrequency());
}

void RpcSerializer::packGlobalStatistics( const GlobalStatistics& stats)
{
	packGlobalCounter( stats.nofDocumentsInserted());
}

void RpcSerializer::packBlockStatistics( const BlockStatistics& stats)
{
	std::vector<BlockStatistics::Element>::const_iterator
		ei = stats.elements().begin(), ee = stats.elements().end();
	packSize( ee-ei);
	for (; ei != ee; ++ei)
	{
		packString( ei->type());
		packInt64( ei->size());
	}
}

void RpcSerializer::packMetaDataRestrictionCompareOperator( MetaDataRestrictionInterface::CompareOperator val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packDatabaseOptions( const DatabaseOptions& val)
{
	packUint( val.opt());
}

void RpcSerializer::packDatabaseConfigType( const DatabaseInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packStorageConfigType( const StorageInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packVectorStorageConfigType( const VectorStorageInterface::ConfigType& val)
{
	packByte( (unsigned char)val);
}

void RpcSerializer::packFeatureOptions( const analyzer::FeatureOptions& val)
{
	packUint( val.opt());
}

void RpcSerializer::packSummaryElement( const SummaryElement& val)
{
	packString( val.name());
	packString( val.value());
	packDouble( val.weight());
	packInt( val.index());
}

void RpcSerializer::packSummarizationVariable( const SummarizationVariable& val)
{
	packString( val.name());
	const RpcInterfaceStub* so = dynamic_cast<const RpcInterfaceStub*>( val.itr());
	if (!so) throw std::runtime_error( _TXT("passing non RPC interface object in RPC call (summarization variable)"));
	packObject( so->classId(), so->objId());
}

void RpcSerializer::packDocumentTermIteratorTerm( const DocumentTermIteratorInterface::Term& val)
{
	packIndex( (Index)val.tf);
	packIndex( (Index)val.firstpos);
	packIndex( val.termno);
}

void RpcSerializer::packSlice( const DatabaseCursorInterface::Slice& val)
{
	packBuffer( val.ptr(), val.size());
}

void RpcSerializer::packTimeStamp( const TimeStamp& val)
{
	packInt( (Index)val.unixtime());
	packInt( (Index)val.counter());
}

void RpcSerializer::packStatisticsMessage( const StatisticsMessage& val)
{
	packTimeStamp( val.timestamp());
	packBuffer( (const char*)val.ptr(), val.size());
}

void RpcSerializer::packAnalyzerDocument( const analyzer::Document& val)
{
	packString( val.subDocumentTypeName());
	std::vector<analyzer::DocumentAttribute>::const_iterator ai = val.attributes().begin(), ae = val.attributes().end();
	packSize( ae-ai);
	for (; ai != ae; ++ai)
	{
		packAnalyzerDocumentAttribute( *ai);
	}
	std::vector<analyzer::DocumentMetaData>::const_iterator mi = val.metadata().begin(), me = val.metadata().end();
	packSize( me-mi);
	for (; mi != me; ++mi)
	{
		packAnalyzerDocumentMetaData( *mi);
	}
	std::vector<analyzer::DocumentTerm>::const_iterator si = val.searchIndexTerms().begin(), se = val.searchIndexTerms().end();
	packSize( se-si);
	for (; si != se; ++si)
	{
		packAnalyzerDocumentTerm( *si);
	}
	std::vector<analyzer::DocumentStructure>::const_iterator xi = val.searchIndexStructures().begin(), xe = val.searchIndexStructures().end();
	packSize( xe-xi);
	for (; xi != xe; ++xi)
	{
		packAnalyzerDocumentStructure( *xi);
	}
	std::vector<analyzer::DocumentTerm>::const_iterator fi = val.forwardIndexTerms().begin(), fe = val.forwardIndexTerms().end();
	packSize( fe-fi);
	for (; fi != fe; ++fi)
	{
		packAnalyzerDocumentTerm( *fi);
	}
	std::vector<std::string>::const_iterator ri = val.accessList().begin(), re = val.accessList().end();
	packSize( re-ri);
	for (; ri != re; ++ri)
	{
		packString( *ri);
	}
}

void RpcSerializer::packAnalyzerQueryTerm( const analyzer::QueryTerm& val)
{
	packString( val.type());
	packString( val.value());
	packIndex( val.len());
}

void RpcSerializer::packAnalyzerQueryTermExpression( const analyzer::QueryTermExpression& val)
{
	std::vector<analyzer::QueryTermExpression::Instruction>::const_iterator
		ii = val.instructions().begin(), ie = val.instructions().end();
	packSize( ie-ii);
	for (; ii != ie; ++ii)
	{
		packByte( ii->opCode());
		switch (ii->opCode())
		{
			case analyzer::QueryTermExpression::Instruction::Term:
			{
				const analyzer::QueryTerm& term = val.term( ii->idx());
				packAnalyzerQueryTerm( term);
				break;
			}
			case analyzer::QueryTermExpression::Instruction::Operator:
				packIndex( ii->idx());
				packIndex( ii->nofOperands());
				break;
		}
	}
}

void RpcSerializer::packAnalyzerDocumentAttribute( const analyzer::DocumentAttribute& val)
{
	packString( val.name());
	packString( val.value());
}

void RpcSerializer::packAnalyzerDocumentMetaData( const analyzer::DocumentMetaData& val)
{
	packString( val.name());
	packNumericVariant( val.value());
}

void RpcSerializer::packAnalyzerDocumentTerm( const analyzer::DocumentTerm& val)
{
	packString( val.type());
	packString( val.value());
	packIndex( val.pos());
}

void RpcSerializer::packAnalyzerDocumentStructure( const analyzer::DocumentStructure& val)
{
	packString( val.name());
	packAnalyzerPositionRange( val.source());
	packAnalyzerPositionRange( val.sink());
}

void RpcSerializer::packAnalyzerPosition( const analyzer::Position& val)
{
	packUint( val.seg());
	packUint( val.ofs());
}

void RpcSerializer::packAnalyzerToken( const analyzer::Token& val)
{
	packUint( val.ordpos());
	packUint( val.origsize());
	packAnalyzerPosition( val.origpos());
}

void RpcSerializer::packDocumentAnalyzerStructureType( const DocumentAnalyzerInstanceInterface::StructureType& val)
{
	packByte( val);
}

void RpcSerializer::packAnalyzerGroupBy( const QueryAnalyzerContextInterface::GroupBy& val)
{
	packByte( val);
}

void RpcSerializer::packAnalyzerPatternLexem( const analyzer::PatternLexem& val)
{
	packUint( val.id());
	packUint( val.ordpos());
	packUint( val.origpos().seg());
	packUint( val.origpos().ofs());
	packUint( val.origsize());
}

void RpcSerializer::packAnalyzerTokenMarkup( const analyzer::TokenMarkup& val)
{
	packString( val.name());
	std::vector<analyzer::TokenMarkup::Attribute>::const_iterator ai = val.attributes().begin(), ae = val.attributes().end();
	packSize( ae-ai);
	for (; ai != ae; ++ai)
	{
		packString( ai->name());
		packString( ai->value());
	}
}

void RpcSerializer::packAnalyzerPatternMatcherResult( const analyzer::PatternMatcherResult& val)
{
	packCharp( val.name());
	packCharp( val.value());
	packUint( val.ordpos());
	packUint( val.ordend());
	packUint( val.origpos().seg());
	packUint( val.origpos().ofs());
	packUint( val.origend().seg());
	packUint( val.origend().ofs());

	std::vector<analyzer::PatternMatcherResult::Item>::const_iterator ri = val.items().begin(), re = val.items().end();
	packSize( re-ri);
	for (; ri != re; ++ri)
	{
		packCharp( ri->name());
		packCharp( ri->value());
		packUint( ri->ordpos());
		packUint( ri->ordend());
		packUint( ri->origpos().seg());
		packUint( ri->origpos().ofs());
		packUint( ri->origend().seg());
		packUint( ri->origend().ofs());
	}
}

void RpcSerializer::packAnalyzerPatternMatcherStatistics( const analyzer::PatternMatcherStatistics& val)
{
	std::vector<analyzer::PatternMatcherStatistics::Item>::const_iterator
		ti = val.items().begin(), te = val.items().end();
	packSize( te-ti);
	for (; ti != te; ++ti)
	{
		packCharp( ti->name());
		packDouble( ti->value());
	}
}

void RpcSerializer::packSegmenterOptions( const analyzer::SegmenterOptions& opts)
{
	std::vector<analyzer::SegmenterOptions::Item>::const_iterator
		oi = opts.items().begin(), oe = opts.items().end();
	packSize( oe-oi);
	for (; oi != oe; ++oi)
	{
		packString( oi->first);
		packString( oi->second);
	}
}

void RpcSerializer::packWeightedDocument( const WeightedDocument& val)
{
	packIndex( val.docno());
	packDouble( val.weight());
}

void RpcSerializer::packResultDocument( const ResultDocument& val)
{
	packWeightedDocument( val);
	std::vector<SummaryElement>::const_iterator
		ai = val.summaryElements().begin(), ae = val.summaryElements().end();
	packSize( ae-ai);
	for (; ai != ae; ++ai)
	{
		packSummaryElement( *ai);
	}
}

void RpcSerializer::packQueryResult( const QueryResult& val)
{
	packByte( val.evaluationPass());
	packIndex( val.nofRanked());
	packIndex( val.nofVisited());

	std::vector<ResultDocument>::const_iterator
		ri = val.ranks().begin(), re = val.ranks().end();
	packSize( re-ri);
	for (; ri != re; ++ri)
	{
		packResultDocument( *ri);
	}
}

void RpcSerializer::packStorageCommitResult( const StorageCommitResult& val)
{
	packBool( val.success());
	packIndex( val.nofDocumentsAffected());
}

void RpcSerializer::packFeatureParameter( const QueryEvalInterface::FeatureParameter& val)
{
	packString( val.featureRole());
	packString( val.featureSet());
}

void RpcSerializer::packDocumentStatisticsType( const StorageClientInterface::DocumentStatisticsType& val)
{
	packByte( val);
}

void RpcSerializer::packTermStatisticsChange( const TermStatisticsChange& val)
{
	packCharp( val.type());
	packCharp( val.value());
	packInt( val.increment());
}

void RpcSerializer::packQueryProcessorFunctionType( const QueryProcessorInterface::FunctionType& val)
{
	packByte((unsigned char)val);
}

void RpcSerializer::packTextProcessorFunctionType( const TextProcessorInterface::FunctionType& val)
{
	packByte((unsigned char)val);
}

void RpcSerializer::packStructView( const StructView& val)
{
	packByte( val.type());
	switch (val.type())
	{
		case StructView::Null:
			break;
		case StructView::String:
			packString( val.asstring());
			break;
		case StructView::Numeric:
			packNumericVariant( val.asnumeric());
			break;
		case StructView::Structure:
		{
			packBool( val.isArray());
			if (val.isArray())
			{
				std::size_t ai = 0, ae = val.arraySize();
				packSize( ae);
				for (; ai != ae; ++ai)
				{
					packStructView( *val.get( ai));
				}
			}
			else
			{
				packSize( val.dictSize());
				StructView::dict_iterator ai = val.dict_begin(), ae = val.dict_end();
				for (; ai != ae; ++ai)
				{
					packString( ai->first);
					packStructView( ai->second);
				}
			}
			break;
		}
	}
	
}

void RpcSerializer::packVectorQueryResult( const VectorQueryResult& val)
{
	packString( val.value());
	packDouble( val.weight());
}

void RpcSerializer::packSentenceTerm( const SentenceTerm& val)
{
	packString( val.type());
	packString( val.value());
}

void RpcSerializer::packSentenceTermList( const SentenceTermList& val)
{
	packSize( val.size());
	std::vector<SentenceTerm>::const_iterator ti = val.begin(), te = val.end();
	for (; ti != te; ++ti)
	{
		packSentenceTerm( *ti);
	}
}

void RpcSerializer::packSentenceGuess( const SentenceGuess& val)
{
	packString( val.classname());
	packSentenceTermList( val.terms());
	packDouble( val.weight());
}

void RpcSerializer::packAnalyzerContentStatisticsItem( const analyzer::ContentStatisticsItem& val)
{
	packString( val.select());
	packString( val.type());
	packString( val.example());
	packInt( val.df());
	packInt( val.tf());
}

void RpcSerializer::packAnalyzerContentStatisticsResult( const analyzer::ContentStatisticsResult& val)
{
	packInt( val.nofDocuments());
	packSize( val.items().size());
	std::vector<analyzer::ContentStatisticsItem>::const_iterator ii = val.items().begin(), ie = val.items().end();
	for (; ii != ie; ++ii)
	{
		packAnalyzerContentStatisticsItem( *ii);
	}
}

void RpcSerializer::packPosTaggerDataElement( const PosTaggerDataInterface::Element& val)
{
	packScalar( m_content, val.type());
	packString( val.tag());
	packString( val.value());
	packString( val.ref());
}

void RpcSerializer::packCrc32()
{
#if STRUS_RPC_PROTOCOL_WITH_CRC32_CHECKSUM
#ifdef STRUS_ALTERNATIVE_CHECK_SUM
	uint32_t crc = calcAlternativeCheckSum( m_content.c_str(), m_content.size());
#else
	uint32_t crc = utils::Crc32::calc( m_content.c_str(), m_content.size());
#endif
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packCrc32(" << crc << ") size=" << m_content.size() << std::endl;
#endif
	packScalar( m_content, crc);
#endif
}

unsigned int RpcDeserializer::unpackSessionId()
{
	CHECK_TYPE( SessionId)
	unsigned int rt = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackSessionId (" << rt << ")" << std::endl;
#endif
	return rt;
}

void RpcDeserializer::unpackObject( unsigned char& classId_, unsigned int& objId_)
{
	CHECK_TYPE( Object)
	classId_ = unpackScalar<char>( m_itr, m_end);
	objId_ = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackObject (" << (unsigned int)classId_ << ", " << objId_ << ")" << std::endl;
#endif
}

std::string RpcDeserializer::unpackString()
{
	CHECK_TYPE( String)
	std::string rt;
	uint32_t strsize = unpackScalar<uint32_t>( m_itr, m_end);
	if (m_itr+strsize > m_end)
	{
		throw std::runtime_error( _TXT("message to small to encode next string"));
	}
	rt.append( m_itr, strsize);
	m_itr += strsize;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackString ('" << rt << "')" << std::endl;
#endif
	return rt;
}

const char* RpcDeserializer::unpackConstCharp()
{
	CHECK_TYPE( Charp)
	const char* start = m_itr;
	while (m_itr < m_end && *m_itr) ++m_itr;
	if (m_itr == m_end)
	{
		throw std::runtime_error( _TXT("message to small to encode next C string"));
	}
	++m_itr;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackConstCharp ('" << start << "')" << std::endl;
#endif
	return start;
}

const char** RpcDeserializer::unpackConstCharpp()
{
	CHECK_TYPE( Charpp)
	std::size_t ii=0,strsize = unpackSize();
	m_charpp_buf.clear();
	m_charpp_buf.reserve( strsize+1);
	for (; ii<strsize; ++ii)
	{
		m_charpp_buf.push_back( unpackConstCharp());
	}
	m_charpp_buf.push_back( 0);
#ifdef STRUS_LOWLEVEL_DEBUG
	const char** pp = (const char**)m_charpp_buf.data();
	char const** gi = pp;
	std::cerr << "unpackConstCharp (";
	for (int gidx=0; *gi; ++gi,++gidx)
	{
		if (gidx) std::cerr << ", ";
		std::cerr << "'" << *gi << "'";
	}
	std::cerr << ")" << std::endl;
#endif
	return (const char**)m_charpp_buf.data();
}

void RpcDeserializer::unpackBuffer( const char*& buf, std::size_t& strsize)
{
	CHECK_TYPE( Buffer)
	strsize = unpackScalar<uint32_t>( m_itr, m_end);
	buf = m_itr;
	m_itr += strsize;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackBuffer('" << std::string(buf,strsize) << "')" << std::endl;
#endif
}

void RpcDeserializer::unpackBuffer( const void*& buf, std::size_t& strsize)
{
	CHECK_TYPE( Buffer)
	strsize = unpackScalar<uint32_t>( m_itr, m_end);
	buf = m_itr;
	m_itr += strsize;
#ifdef STRUS_LOWLEVEL_DEBUG
	strus_hexdump( stderr, (const char*)buf, strsize);
	fprintf( stderr, "\n");
#endif
}

std::vector<double> RpcDeserializer::unpackBufferFloat()
{
	CHECK_TYPE( BufferFloat)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::ostringstream msg;
#endif
	std::vector<double> rt;
	std::size_t ii=0, strsize = unpackScalar<uint32_t>( m_itr, m_end);
	for (ii=0; ii<strsize; ++ii)
	{
		rt.push_back( unpackDouble());
#ifdef STRUS_LOWLEVEL_DEBUG
		if (ii) msg << ", ";
		msg << rt.back();
#endif
	}
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackBufferFloat('" << msg.str() << "')" << std::endl;
#endif
	return rt;
}

bool RpcDeserializer::unpackBool()
{
	CHECK_TYPE( Bool)
	bool rt = (unpackScalar<uint8_t>( m_itr, m_end) != 0)?true:false;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackBool(" << (rt?"true":"false") << ")" << std::endl;
#endif
	return rt;
}

unsigned char RpcDeserializer::unpackByte()
{
	CHECK_TYPE( Byte)
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackByte(" << (unsigned int)(unsigned char)(*m_itr) << ")" << std::endl;
#endif
	return unpackScalar<uint8_t>( m_itr, m_end);
}

Index RpcDeserializer::unpackIndex()
{
	CHECK_TYPE( Index)
	Index rt = unpackScalar<Index>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackIndex(" << rt << ")" << std::endl;
#endif
	return rt;
}

IndexRange RpcDeserializer::unpackIndexRange()
{
	CHECK_TYPE( IndexRange)
	Index start = unpackScalar<Index>( m_itr, m_end);
	Index end = unpackScalar<Index>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackIndexRange (" << (int)start << "," << (int)end << ")" << std::endl;
#endif
	return IndexRange( start, end);
}

GlobalCounter RpcDeserializer::unpackGlobalCounter()
{
	CHECK_TYPE( GlobalCounter)
	GlobalCounter rt = unpackScalar<GlobalCounter>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackGlobalCounter(" << rt << ")" << std::endl;
#endif
	return rt;
}

unsigned int RpcDeserializer::unpackUint()
{
	CHECK_TYPE( Uint)
	unsigned int rt = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackUint(" << rt << ")" << std::endl;
#endif
	return rt;
}

int RpcDeserializer::unpackInt()
{
	CHECK_TYPE( Int)
	int rt = unpackScalar<int32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackInt(" << rt << ")" << std::endl;
#endif
	return rt;
}

uint64_t RpcDeserializer::unpackUint64()
{
	CHECK_TYPE( Uint64)
	uint64_t rt = unpackScalar<uint64_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackUint64(" << rt << ")" << std::endl;
#endif
	return rt;
}

int64_t RpcDeserializer::unpackInt64()
{
	CHECK_TYPE( Int64)
	int64_t rt = unpackScalar<int64_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackInt64(" << rt << ")" << std::endl;
#endif
	return rt;
}

float RpcDeserializer::unpackFloat()
{
	CHECK_TYPE( Float)
	float rt = unpackScalar<float>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackFloat(" << rt << ")" << std::endl;
#endif
	return rt;
}

double RpcDeserializer::unpackDouble()
{
	CHECK_TYPE( Double)
	float rt = unpackScalar<double>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackDouble(" << rt << ")" << std::endl;
#endif
	return rt;
}

std::size_t RpcDeserializer::unpackSize()
{
	CHECK_TYPE( Size)
	unsigned int rt = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackSize(" << rt << ")" << std::endl;
#endif
	return rt;
}

NumericVariant RpcDeserializer::unpackNumericVariant()
{
	CHECK_TYPE( NumericVariant)
	NumericVariant::Type type = (NumericVariant::Type)unpackByte();
	switch (type)
	{
		case NumericVariant::Null: return NumericVariant();
		case NumericVariant::Int: return NumericVariant::asint( unpackInt64());
		case NumericVariant::UInt: return NumericVariant::asuint( unpackUint64());
		case NumericVariant::Float: return NumericVariant::asdouble( unpackDouble());
	}
	throw std::runtime_error( _TXT("unknown type of numeric variant"));
}

analyzer::DocumentClass RpcDeserializer::unpackDocumentClass()
{
	analyzer::DocumentClass rt( unpackString());
	rt.setSchema( unpackString());
	rt.setEncoding( unpackString());
	return rt;
}

analyzer::DocumentStructure::PositionRange RpcDeserializer::unpackAnalyzerPositionRange()
{
	int start = unpackInt();
	int end = unpackInt();
	return analyzer::DocumentStructure::PositionRange( start, end);
}

TermStatistics RpcDeserializer::unpackTermStatistics()
{
	TermStatistics rt;
	rt.setDocumentFrequency( unpackGlobalCounter());
	return rt;
}

GlobalStatistics RpcDeserializer::unpackGlobalStatistics()
{
	GlobalStatistics rt;
	rt.setNofDocumentsInserted( unpackGlobalCounter());
	return rt;
}

BlockStatistics RpcDeserializer::unpackBlockStatistics()
{
	std::vector<BlockStatistics::Element> elements;
	std::size_t ei=0, ee=unpackSize();
	for (; ei != ee; ++ei)
	{
		std::string type = unpackString();
		int64_t sz = unpackInt64();
		elements.push_back( BlockStatistics::Element( type, sz));
	}
	return BlockStatistics( elements);
}

MetaDataRestrictionInterface::CompareOperator RpcDeserializer::unpackMetaDataRestrictionCompareOperator()
{
	return (MetaDataRestrictionInterface::CompareOperator)unpackByte();
}

bool RpcDeserializer::unpackCrc32()
{
#if STRUS_RPC_PROTOCOL_WITH_CRC32_CHECKSUM	
	uint32_t strsize = (m_end - m_start) - 4;
#ifdef STRUS_ALTERNATIVE_CHECK_SUM
	uint32_t crc = calcAlternativeCheckSum( m_start, strsize);
#else
	uint32_t crc = utils::Crc32::calc( m_start, strsize);
#endif
	char const* ee = m_end-4;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackCrc32(" << crc << ") size=" << strsize << std::endl;
#endif
#ifdef STRUS_ALTERNATIVE_CHECK_SUM
	if (checkAlternativeCheckSum( crc, unpackScalar<uint32_t>( ee, m_end)))
	{
		return true;
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		strus_hexdump( stderr, "CRC32 checksum failed", (const unsigned char*)m_start, (size_t)strsize);
#endif
		return false;
	}
#else
	return crc == unpackScalar<uint32_t>( ee, m_end);
#endif
#else
	return true;
#endif
}

WordVector RpcDeserializer::unpackWordVector()
{
	std::size_t ii=0, ie=unpackSize();
	WordVector rt;

	for (; ii != ie; ++ii)
	{
		rt.push_back( unpackFloat());
	}
	return rt;
}

StructureLink RpcDeserializer::unpackStructureLink()
{
	bool header = unpackBool();
	strus::Index structno = unpackIndex();
	int index = unpackIndex();
	return StructureLink( structno, header, index);
}

StructureLinkArray RpcDeserializer::unpackStructureLinkArray()
{
	int li=0, nofLinks = unpackSize();
	if (li < 0 || li > StructureLinkArray::MaxNofLinks)
	{
		throw std::runtime_error( _TXT("number of links out of range"));
	}
	StructureLink lar[ StructureLinkArray::MaxNofLinks];
	for (; li < nofLinks; ++li)
	{
		lar[ li] = unpackStructureLink();
	}
	return StructureLinkArray( lar, nofLinks);
}


DatabaseOptions RpcDeserializer::unpackDatabaseOptions()
{
	return DatabaseOptions( unpackUint());
}

DatabaseInterface::ConfigType RpcDeserializer::unpackDatabaseConfigType()
{
	return DatabaseInterface::ConfigType( unpackByte());
}

StorageInterface::ConfigType RpcDeserializer::unpackStorageConfigType()
{
	return StorageInterface::ConfigType( unpackByte());
}

VectorStorageInterface::ConfigType RpcDeserializer::unpackVectorStorageConfigType()
{
	return VectorStorageInterface::ConfigType( unpackByte());
}

analyzer::FeatureOptions RpcDeserializer::unpackFeatureOptions()
{
	return analyzer::FeatureOptions( unpackUint());
}

SummaryElement RpcDeserializer::unpackSummaryElement()
{
	std::string name = unpackString();
	std::string value = unpackString();
	float weight = unpackDouble();
	float index = unpackInt();
	return SummaryElement( name, value, weight, index);
}

DocumentTermIteratorInterface::Term RpcDeserializer::unpackDocumentTermIteratorTerm()
{
	Index tf = unpackIndex();
	Index firstpos = unpackIndex();
	Index termno = unpackIndex();
	return DocumentTermIteratorInterface::Term( tf, firstpos, termno);
}

DatabaseCursorInterface::Slice RpcDeserializer::unpackSlice()
{
	const char* buf;
	std::size_t strsize;
	unpackBuffer( buf, strsize);
	DatabaseCursorInterface::Slice rt( buf, strsize);
	return rt;
}

TimeStamp RpcDeserializer::unpackTimeStamp()
{
	int unixtime = unpackInt();
	int counter = unpackInt();
	return TimeStamp( unixtime, counter);
}

StatisticsMessage RpcDeserializer::unpackStatisticsMessage()
{
	TimeStamp tm = unpackTimeStamp();
	const char* buf;
	std::size_t bufsize;
	unpackBuffer( buf, bufsize);
	return StatisticsMessage( buf, bufsize, tm);
}

analyzer::Document RpcDeserializer::unpackAnalyzerDocument()
{
	analyzer::Document rt;
	rt.setSubDocumentTypeName( unpackString());
	std::size_t ii=0,strsize=unpackSize();
	for (; ii<strsize; ++ii)
	{
		analyzer::DocumentAttribute attr = unpackAnalyzerDocumentAttribute();
		rt.setAttribute( attr.name(), attr.value());
	}
	for (ii=0,strsize=unpackSize(); ii<strsize; ++ii)
	{
		analyzer::DocumentMetaData md = unpackAnalyzerDocumentMetaData();
		rt.setMetaData( md.name(), md.value());
	}
	for (ii=0,strsize=unpackSize(); ii<strsize; ++ii)
	{
		analyzer::DocumentTerm term = unpackAnalyzerDocumentTerm();
		rt.addSearchIndexTerm( term.type(), term.value(), term.pos());
	}
	for (ii=0,strsize=unpackSize(); ii<strsize; ++ii)
	{
		analyzer::DocumentStructure stu = unpackAnalyzerDocumentStructure();
		rt.addSearchIndexStructure( stu.name(), stu.source(), stu.sink());
	}
	for (ii=0,strsize=unpackSize(); ii<strsize; ++ii)
	{
		analyzer::DocumentTerm term = unpackAnalyzerDocumentTerm();
		rt.addForwardIndexTerm( term.type(), term.value(), term.pos());
	}
	for (ii=0,strsize=unpackSize(); ii<strsize; ++ii)
	{
		std::string userRole = unpackString();
		rt.addAccess( userRole);
	}
	return rt;
}

analyzer::QueryTerm RpcDeserializer::unpackAnalyzerQueryTerm()
{
	std::string type = unpackString();
	std::string value = unpackString();
	unsigned int len = (unsigned int)unpackIndex();
	return analyzer::QueryTerm( type, value, len);
}

analyzer::QueryTermExpression RpcDeserializer::unpackAnalyzerQueryTermExpression()
{
	analyzer::QueryTermExpression rt;
	std::size_t ii=0,strsize=unpackSize();
	for (; ii<strsize; ++ii)
	{
		analyzer::QueryTermExpression::Instruction::OpCode
			opCode = (analyzer::QueryTermExpression::Instruction::OpCode)unpackByte();
		switch (opCode)
		{
			case analyzer::QueryTermExpression::Instruction::Term:
				rt.pushTerm( unpackAnalyzerQueryTerm());
				break;
			case analyzer::QueryTermExpression::Instruction::Operator:
			{
				unsigned int operatorId = unpackIndex();
				unsigned int nofOperands = unpackIndex();
				rt.pushOperator( operatorId, nofOperands);
				break;
			}
		}
	}
	return rt;
}

analyzer::DocumentAttribute RpcDeserializer::unpackAnalyzerDocumentAttribute()
{
	std::string name = unpackString();
	std::string value = unpackString();
	return analyzer::DocumentAttribute( name, value);
}

analyzer::DocumentMetaData RpcDeserializer::unpackAnalyzerDocumentMetaData()
{
	std::string name = unpackString();
	NumericVariant value = unpackNumericVariant();
	return analyzer::DocumentMetaData( name, value);
}

analyzer::DocumentTerm RpcDeserializer::unpackAnalyzerDocumentTerm()
{
	std::string type = unpackString();
	std::string value = unpackString();
	unsigned int pos = (unsigned int)unpackIndex();
	return analyzer::DocumentTerm( type, value, pos);
}

analyzer::DocumentStructure RpcDeserializer::unpackAnalyzerDocumentStructure()
{
	std::string name = unpackString();
	analyzer::DocumentStructure::PositionRange source = unpackAnalyzerPositionRange();
	analyzer::DocumentStructure::PositionRange sink = unpackAnalyzerPositionRange();
	return analyzer::DocumentStructure( name, source, sink);
}

analyzer::Position RpcDeserializer::unpackAnalyzerPosition()
{
	int seg = unpackUint();
	int ofs = unpackUint();
	return analyzer::Position( seg, ofs);
}

analyzer::Token RpcDeserializer::unpackAnalyzerToken()
{
	int ordpos = unpackUint();
	int origsize = unpackUint();
	analyzer::Position origpos( unpackAnalyzerPosition());
	return analyzer::Token( ordpos, origpos, origsize);
}

DocumentAnalyzerInstanceInterface::StructureType RpcDeserializer::unpackDocumentAnalyzerStructureType()
{
	return (DocumentAnalyzerInstanceInterface::StructureType)unpackByte();
}

QueryAnalyzerContextInterface::GroupBy RpcDeserializer::unpackAnalyzerGroupBy()
{
	return (QueryAnalyzerContextInterface::GroupBy)unpackByte();
}

analyzer::PatternLexem RpcDeserializer::unpackAnalyzerPatternLexem()
{
	unsigned int id = unpackUint();
	unsigned int ordpos = unpackUint();
	unsigned int origseg = unpackUint();
	unsigned int origpos = unpackUint();
	unsigned int origsize = unpackUint();
	return analyzer::PatternLexem( id, ordpos, analyzer::Position(origseg, origpos), origsize);
}

analyzer::TokenMarkup RpcDeserializer::unpackAnalyzerTokenMarkup()
{
	analyzer::TokenMarkup rt( unpackString());
	std::size_t ii = 0, strsize = unpackSize();
	for (; ii < strsize; ++ii)
	{
		rt( unpackString(), unpackString());
	}
	return rt;
}

analyzer::PatternMatcherResult RpcDeserializer::unpackAnalyzerPatternMatcherResult()
{
	const char* name = unpackConstCharp();
	const char* value = unpackConstCharp();
	unsigned int start_ordpos = unpackUint();
	unsigned int end_ordpos = unpackUint();
	unsigned int start_origseg = unpackUint();
	unsigned int start_origpos = unpackUint();
	unsigned int end_origseg = unpackUint();
	unsigned int end_origpos = unpackUint();

	std::vector<analyzer::PatternMatcherResult::Item> itemlist;
	std::size_t ii = 0, strsize = unpackSize();
	for (; ii < strsize; ++ii)
	{
		const char* i_name( unpackConstCharp());
		const char* i_value( unpackConstCharp());
		unsigned int i_start_ordpos = unpackUint();
		unsigned int i_end_ordpos = unpackUint();
		unsigned int i_start_origseg = unpackUint();
		unsigned int i_start_origpos = unpackUint();
		unsigned int i_end_origseg = unpackUint();
		unsigned int i_end_origpos = unpackUint();

		analyzer::PatternMatcherResult::Item
			item( i_name, i_value, i_start_ordpos, i_end_ordpos,
			analyzer::Position(i_start_origseg, i_start_origpos),
			analyzer::Position(i_end_origseg, i_end_origpos));
		itemlist.push_back( item);
	}
	analyzer::PatternMatcherResult rt( name, value, start_ordpos, end_ordpos, analyzer::Position(start_origseg, start_origpos), analyzer::Position(end_origseg, end_origpos), itemlist);
	return rt;
}

analyzer::PatternMatcherStatistics RpcDeserializer::unpackAnalyzerPatternMatcherStatistics()
{
	analyzer::PatternMatcherStatistics rt;
	std::size_t ii = 0, strsize = unpackSize();
	for (; ii < strsize; ++ii)
	{
		rt.define( unpackConstCharp(), unpackDouble());
	}
	return rt;
}

analyzer::SegmenterOptions RpcDeserializer::unpackSegmenterOptions()
{
	analyzer::SegmenterOptions rt;
	std::size_t ii = 0, strsize = unpackSize();
	for (; ii < strsize; ++ii)
	{
		rt( unpackString(), unpackString());
	}
	return rt;
}

WeightedDocument RpcDeserializer::unpackWeightedDocument()
{
	Index docno = unpackIndex();
	float weight = unpackDouble();
	return WeightedDocument( docno, weight);
}

ResultDocument RpcDeserializer::unpackResultDocument()
{
	WeightedDocument weightedDocument( unpackWeightedDocument());
	std::vector<SummaryElement> summaryElements;
	std::size_t ii=0,strsize=unpackSize();
	for (; ii<strsize; ++ii)
	{
		summaryElements.push_back( unpackSummaryElement());
	}
	return ResultDocument( weightedDocument, summaryElements);
}

QueryResult RpcDeserializer::unpackQueryResult()
{
	unsigned int pass = unpackByte();
	unsigned int nofRanked = unpackIndex();
	unsigned int nofVisited = unpackIndex();
	std::size_t ii=0,strsize=unpackSize();
	std::vector<ResultDocument> ranks;
	for (; ii<strsize; ++ii)
	{
		ranks.push_back( unpackResultDocument());
	}
	return QueryResult( pass, nofRanked, nofVisited, ranks);
}

StorageCommitResult RpcDeserializer::unpackStorageCommitResult()
{
	bool success = unpackBool();
	strus::Index nofDocumentsAffected = unpackIndex();
	return StorageCommitResult( success, nofDocumentsAffected);
}

QueryEvalInterface::FeatureParameter RpcDeserializer::unpackFeatureParameter()
{
	std::string featureRole = unpackString();
	std::string featureSet = unpackString();
	return QueryEvalInterface::FeatureParameter( featureRole, featureSet);
}

StorageClientInterface::DocumentStatisticsType RpcDeserializer::unpackDocumentStatisticsType()
{
	return (StorageClientInterface::DocumentStatisticsType)unpackByte();
}

TermStatisticsChange RpcDeserializer::unpackTermStatisticsChange()
{
	const char* type = unpackConstCharp();
	const char* value = unpackConstCharp();
	int increment = unpackInt();
	return TermStatisticsChange( type, value, increment);
}

QueryProcessorInterface::FunctionType RpcDeserializer::unpackQueryProcessorFunctionType()
{
	return (QueryProcessorInterface::FunctionType)unpackByte();
}

TextProcessorInterface::FunctionType RpcDeserializer::unpackTextProcessorFunctionType()
{
	return (TextProcessorInterface::FunctionType)unpackByte();
}

StructView RpcDeserializer::unpackStructView()
{
	StructView::Type type = (StructView::Type)unpackByte();
	switch (type)
	{
		case StructView::Null:
			return StructView();
		case StructView::String:
			return StructView( unpackString());
		case StructView::Numeric:
			return StructView( unpackNumericVariant());
		case StructView::Structure:
		{
			StructView rt;
			bool isArray = unpackBool();
			if (isArray)
			{
				std::size_t ai = 0, ae = unpackSize();
				for (; ai != ae; ++ai)
				{
					rt( unpackStructView());
				}
			}
			else
			{
				std::size_t ai = 0, ae = unpackSize();
				for (; ai != ae; ++ai)
				{
					rt( unpackString(), unpackStructView());
				}
			}
			return rt;
		}
	}
	return StructView();
}

VectorQueryResult RpcDeserializer::unpackVectorQueryResult()
{
	std::string value = unpackString();
	double weight = unpackDouble();
	return VectorQueryResult( value, weight);
}

SentenceTerm RpcDeserializer::unpackSentenceTerm()
{
	std::string type = unpackString();
	std::string value = unpackString();
	return SentenceTerm( type, value);
}

SentenceTermList RpcDeserializer::unpackSentenceTermList()
{
	SentenceTermList rt;
	unsigned int ii=0, nn=unpackSize();
	rt.reserve( nn);
	for (; ii<nn; ++ii)
	{
		rt.push_back( unpackSentenceTerm());
	}
	return rt;
}

SentenceGuess RpcDeserializer::unpackSentenceGuess()
{
	std::string classname( unpackString());
	std::vector<SentenceTerm> terms( unpackSentenceTermList());
	double weight = unpackDouble();

	return SentenceGuess( classname, terms, weight);
}

analyzer::ContentStatisticsItem RpcDeserializer::unpackAnalyzerContentStatisticsItem()
{
	std::string select = unpackString();
	std::string type = unpackString();
	std::string example = unpackString();
	int df = unpackInt();
	int tf = unpackInt();
	return analyzer::ContentStatisticsItem( select, type, example, df, tf);
}

analyzer::ContentStatisticsResult RpcDeserializer::unpackAnalyzerContentStatisticsResult()
{
	int nofDocuments = unpackInt();
	std::vector<analyzer::ContentStatisticsItem> items;
	int ii=0, ie = unpackSize();
	for (; ii != ie; ++ii)
	{
		items.push_back( unpackAnalyzerContentStatisticsItem());
	}
	return analyzer::ContentStatisticsResult( nofDocuments, items);
}

PosTaggerDataInterface::Element RpcDeserializer::unpackPosTaggerDataElement()
{
	PosTaggerDataInterface::Element::Type type = unpackScalar<PosTaggerDataInterface::Element::Type>( m_itr, m_end);
	std::string tag = unpackString();
	std::string value = unpackString();
	std::string ref = unpackString();
	return PosTaggerDataInterface::Element( type, tag, value, ref);
}


