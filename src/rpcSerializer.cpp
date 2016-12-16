/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "rpcSerializer.hpp"
#include "hexdump.h"
#include "private/utils.hpp"
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
	if (itr+1 > end) throw strus::runtime_error( _TXT("message to small to encode next byte"));
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
	if (itr+2 > end) throw strus::runtime_error( _TXT("message to small to encode next word"));
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
		throw strus::runtime_error( _TXT("message to small to encode next dword"));
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
	if (itr+8 > end) throw strus::runtime_error( _TXT("message to small to encode next qword"));
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

void RpcSerializer::packSessionId( unsigned int id_)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packSessionId " << id_ << std::endl;
#endif
	packScalar( m_content, (uint32_t)id_);
}

void RpcSerializer::packObject( unsigned char classId_, unsigned int objId_)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packObject (" << (unsigned int)classId_ << ", " << objId_ << ")" << std::endl;
#endif
	if (objId_ > std::numeric_limits<uint32_t>::max()) throw strus::runtime_error( _TXT("object id out of range"));
	packScalar( m_content, classId_);
	packScalar( m_content, (uint32_t)objId_);
}

void RpcSerializer::packString( const std::string& str)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packString ('" << str << "')" << std::endl;
#endif
	if (str.size() > std::numeric_limits<uint32_t>::max()) throw strus::runtime_error( _TXT("string size out of range"));
	packScalar( m_content, (uint32_t)str.size());
	m_content.append( str);
	
}

void RpcSerializer::packCharp( const char* buf)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packCharp ('" << buf << "')" << std::endl;
#endif
	if (buf) m_content.append( buf);
	m_content.push_back( '\0');
}

void RpcSerializer::packCharpp( const char** buf)
{
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
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packBuffer('" << std::string(buf,size) << "')" << std::endl;
#endif
	if (size > std::numeric_limits<uint32_t>::max()) throw strus::runtime_error( _TXT("buffer size out of range"));
	packScalar( m_content, (uint32_t)size);
	m_content.append( buf, size);
}

void RpcSerializer::packBufferFloat( const double* buf, std::size_t size)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packBufferFloat( ... )" << std::endl;
#endif
	if (size > std::numeric_limits<uint32_t>::max()) throw strus::runtime_error( _TXT("buffer size out of range"));
	packScalar( m_content, (uint32_t)size);
	std::size_t ii=0;
	for (ii=0; ii<size; ++ii)
	{
		packDouble( buf[ii]);
	}
}

void RpcSerializer::packBool( bool val)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packBool(" << (val?"true":"false") << ")" << std::endl;
#endif
	m_content.push_back( val?1:0);
}

void RpcSerializer::packByte( unsigned char val)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packByte (" << (unsigned int)val << ")" << std::endl;
#endif
	m_content.push_back( val);
}

void RpcSerializer::packIndex( const Index& index)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packIndex (" << (unsigned int)index << ")" << std::endl;
#endif
	packScalar( m_content, index);
}

void RpcSerializer::packGlobalCounter( const GlobalCounter& index)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packGlobalCounter (" << (uintptr_t)index << ")" << std::endl;
#endif
	packScalar( m_content, index);
}

void RpcSerializer::packUint( unsigned int val)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packUint (" << (unsigned int)val << ")" << std::endl;
#endif
	if (val > std::numeric_limits<uint32_t>::max()) throw strus::runtime_error( _TXT("packed uint out of range"));
	packScalar( m_content, (uint32_t)val);
}

void RpcSerializer::packInt( int val)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packInt (" << (signed int)val << ")" << std::endl;
#endif
	if (val > std::numeric_limits<int32_t>::max()
	||  val < std::numeric_limits<int32_t>::min()) throw strus::runtime_error( _TXT("packed int out of range"));
	packScalar( m_content, (int32_t)val);
}

void RpcSerializer::packFloat( float val)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packFloat (" << (float)val << ")" << std::endl;
#endif
	pack<sizeof(float)>( m_content, &val);
}

void RpcSerializer::packDouble( double val)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packDouble(" << (double)val << ")" << std::endl;
#endif
	pack<sizeof(double)>( m_content, &val);
}

void RpcSerializer::packSize( std::size_t size)
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "packSize (" << (std::size_t)size << ")" << std::endl;
#endif
	if (size > std::numeric_limits<uint32_t>::max()) throw strus::runtime_error( _TXT("packed size out of range"));
	packScalar( m_content, (uint32_t)size);
}

void RpcSerializer::packNumericVariant( const NumericVariant& val)
{
	packByte( (unsigned char)val.type);
	switch (val.type)
	{
		case NumericVariant::Null: break;
		case NumericVariant::Int: packInt( val.variant.Int); break;
		case NumericVariant::UInt: packUint( val.variant.UInt); break;
		case NumericVariant::Float: packDouble( val.variant.Float); break;
	}
}

void RpcSerializer::packDocumentClass( const analyzer::DocumentClass& dclass)
{
	packString( dclass.mimeType());
	packString( dclass.scheme());
	packString( dclass.encoding());
}

void RpcSerializer::packTermStatistics( const TermStatistics& stats)
{
	packGlobalCounter( stats.documentFrequency());
}

void RpcSerializer::packGlobalStatistics( const GlobalStatistics& stats)
{
	packGlobalCounter( stats.nofDocumentsInserted());
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
	if (!so) throw strus::runtime_error( _TXT("passing non RPC interface object in RPC call (summarization variable)"));
	packObject( so->classId(), so->objId());
}

void RpcSerializer::packDocumentTermIteratorTerm( const DocumentTermIteratorInterface::Term& val)
{
	packIndex( (Index)val.tf);
	packIndex( (Index)val.firstpos);
	packIndex( val.termno);
}

void RpcSerializer::packSlice( DatabaseCursorInterface::Slice& val)
{
	packBuffer( val.ptr(), val.size());
}

void RpcSerializer::packAnalyzerDocument( const analyzer::Document& val)
{
	packString( val.subDocumentTypeName());
	std::vector<analyzer::Attribute>::const_iterator ai = val.attributes().begin(), ae = val.attributes().end();
	packSize( ae-ai);
	for (; ai != ae; ++ai)
	{
		packAnalyzerAttribute( *ai);
	}
	std::vector<analyzer::MetaData>::const_iterator mi = val.metadata().begin(), me = val.metadata().end();
	packSize( me-mi);
	for (; mi != me; ++mi)
	{
		packAnalyzerMetaData( *mi);
	}
	std::vector<analyzer::Term>::const_iterator si = val.searchIndexTerms().begin(), se = val.searchIndexTerms().end();
	packSize( se-si);
	for (; si != se; ++si)
	{
		packAnalyzerTerm( *si);
	}
	std::vector<analyzer::Term>::const_iterator fi = val.forwardIndexTerms().begin(), fe = val.forwardIndexTerms().end();
	packSize( fe-fi);
	for (; fi != fe; ++fi)
	{
		packAnalyzerTerm( *fi);
	}
}

void RpcSerializer::packAnalyzerQuery( const analyzer::Query& val)
{
	{
		std::vector<analyzer::Query::Element>::const_iterator
			ei = val.elements().begin(), ee = val.elements().end();
		packSize( ee-ei);
		for (; ei != ee; ++ei)
		{
			packByte( ei->type());
			switch (ei->type())
			{
				case analyzer::Query::Element::MetaData:
					packAnalyzerMetaData( val.metadata( ei->idx()));
					break;
				case analyzer::Query::Element::SearchIndexTerm:
					packAnalyzerTerm( val.searchIndexTerm( ei->idx()));
					break;
			}
			packIndex( ei->position());
			packIndex( ei->fieldNo());
		}
	}
	{
		std::vector<analyzer::Query::Instruction>::const_iterator
			ci = val.instructions().begin(), ce = val.instructions().end();
		packSize( ce-ci);
		for (; ci != ce; ++ci)
		{
			packByte( ci->opCode());
			switch (ci->opCode())
			{
				case analyzer::Query::Instruction::PushMetaData:
				case analyzer::Query::Instruction::PushSearchIndexTerm:
					packIndex( ci->idx());
					break;
				case analyzer::Query::Instruction::Operator:
				{
					packIndex( ci->idx());
					packIndex( ci->nofOperands());
					break;
				}
			}
		}
	}
}

void RpcSerializer::packAnalyzerAttribute( const analyzer::Attribute& val)
{
	packString( val.name());
	packString( val.value());
}

void RpcSerializer::packAnalyzerMetaData( const analyzer::MetaData& val)
{
	packString( val.name());
	packNumericVariant( val.value());
}

void RpcSerializer::packAnalyzerTerm( const analyzer::Term& val)
{
	packString( val.type());
	packString( val.value());
	packIndex( val.pos());
}

void RpcSerializer::packAnalyzerTermArray( const analyzer::TermArray& val)
{
	analyzer::TermArray::const_iterator ti = val.begin(), te = val.end();
	packSize( te-ti);
	for (; ti != te; ++ti)
	{
		packAnalyzerTerm( *ti);
	}
}

void RpcSerializer::packAnalyzerToken( const analyzer::Token& val)
{
	packUint( val.ordpos());
	packUint( val.origseg());
	packUint( val.origpos());
	packUint( val.origsize());
}

void RpcSerializer::packAnalyzerGroupBy( const QueryAnalyzerContextInterface::GroupBy& val)
{
	packByte( val);
}

void RpcSerializer::packAnalyzerPatternLexem( const analyzer::PatternLexem& val)
{
	packUint( val.id());
	packUint( val.ordpos());
	packUint( val.origseg());
	packUint( val.origpos());
	packUint( val.origsize());
}

void RpcSerializer::packAnalyzerPatternLexerOptions( const analyzer::PatternLexerOptions& val)
{
	analyzer::PatternLexerOptions::const_iterator oi = val.begin(), oe = val.end();
	packSize( oe-oi);
	for (; oi != oe; ++oi)
	{
		packString( *oi);
	}
}

void RpcSerializer::packAnalyzerPatternMatcherOptions( const analyzer::PatternMatcherOptions& val)
{
	analyzer::PatternMatcherOptions::const_iterator oi = val.begin(), oe = val.end();
	packSize( oe-oi);
	for (; oi != oe; ++oi)
	{
		packString( oi->first);
		packDouble( oi->second);
	}
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
	packUint( val.ordpos());
	packUint( val.start_origseg());
	packUint( val.start_origpos());
	packUint( val.end_origseg());
	packUint( val.end_origpos());

	std::vector<analyzer::PatternMatcherResult::Item>::const_iterator ri = val.items().begin(), re = val.items().end();
	packSize( re-ri);
	for (; ri != re; ++ri)
	{
		packCharp( ri->name());
		packUint( ri->ordpos());
		packUint( ri->start_origseg());
		packUint( ri->start_origpos());
		packUint( ri->end_origseg());
		packUint( ri->end_origpos());
		packDouble( ri->weight());
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
	packIndex( val.nofDocumentsRanked());
	packIndex( val.nofDocumentsVisited());

	std::vector<ResultDocument>::const_iterator
		ri = val.ranks().begin(), re = val.ranks().end();
	packSize( re-ri);
	for (; ri != re; ++ri)
	{
		packResultDocument( *ri);
	}
}

void RpcSerializer::packFeatureParameter( const QueryEvalInterface::FeatureParameter& val)
{
	packString( val.parameterName());
	packString( val.featureSet());
}

void RpcSerializer::packDocumentStatisticsType( const StorageClientInterface::DocumentStatisticsType& val)
{
	packByte( val);
}

void RpcSerializer::packStatisticsProcessorBuilderOptions( const StatisticsProcessorInterface::BuilderOptions& val)
{
	packUint( val.maxBlockSize);
	packByte( val.set);
}

void RpcSerializer::packStatisticsViewerDocumentFrequencyChange( const StatisticsViewerInterface::DocumentFrequencyChange& val)
{
	packCharp( val.type);
	packCharp( val.value);
	packInt( val.increment);
}


void RpcSerializer::packQueryProcessorFunctionType( const QueryProcessorInterface::FunctionType& val)
{
	packByte((unsigned char)val);
}

void RpcSerializer::packTextProcessorFunctionType( const TextProcessorInterface::FunctionType& val)
{
	packByte((unsigned char)val);
}

void RpcSerializer::packPostingJoinOperatorDescription( const PostingJoinOperatorInterface::Description& val)
{
	packString( val.text());
}

void RpcSerializer::packFunctionDescription( const FunctionDescription& val)
{
	packString( val.text());
	packSize( val.parameter().size());
	std::vector<FunctionDescription::Parameter>::const_iterator vi = val.parameter().begin(), ve = val.parameter().end();
	for (; vi != ve; ++vi)
	{
		packByte( (unsigned char)vi->type());
		packString( vi->name());
		packString( vi->text());
		packString( vi->domain());
	}
}

void RpcSerializer::packVectorStorageSearchResult( const VectorStorageSearchInterface::Result& val)
{
	packIndex( val.featidx());
	packDouble( val.weight());
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
	unsigned int rt = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackSessionId (" << rt << ")" << std::endl;
#endif
	return rt;
}

void RpcDeserializer::unpackObject( unsigned char& classId_, unsigned int& objId_)
{
	classId_ = unpackScalar<char>( m_itr, m_end);
	objId_ = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackObject (" << (unsigned int)classId_ << ", " << objId_ << ")" << std::endl;
#endif
}

std::string RpcDeserializer::unpackString()
{
	std::string rt;
	uint32_t size = unpackScalar<uint32_t>( m_itr, m_end);
	if (m_itr+size > m_end)
	{
		throw strus::runtime_error( _TXT("message to small to encode next string"));
	}
	rt.append( m_itr, size);
	m_itr += size;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackString ('" << rt << "')" << std::endl;
#endif
	return rt;
}

const char* RpcDeserializer::unpackConstCharp()
{
	const char* start = m_itr;
	while (m_itr < m_end && *m_itr) ++m_itr;
	if (m_itr == m_end)
	{
		throw strus::runtime_error( _TXT("message to small to encode next C string"));
	}
	++m_itr;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackConstCharp ('" << start << "')" << std::endl;
#endif
	return start;
}

const char** RpcDeserializer::unpackConstCharpp()
{
	std::size_t ii=0,size = unpackSize();
	m_charpp_buf.clear();
	m_charpp_buf.reserve( size+1);
	for (; ii<size; ++ii)
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

void RpcDeserializer::unpackBuffer( const char*& buf, std::size_t& size)
{
	size = unpackScalar<uint32_t>( m_itr, m_end);
	buf = m_itr;
	m_itr += size;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackBuffer('" << std::string(buf,size) << "')" << std::endl;
#endif
}

std::vector<double> RpcDeserializer::unpackBufferFloat()
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::ostringstream msg;
#endif
	std::vector<double> rt;
	std::size_t ii=0, size = unpackScalar<uint32_t>( m_itr, m_end);
	for (ii=0; ii<size; ++ii)
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
	bool rt = (*m_itr++ != 0)?true:false;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackBool(" << (rt?"true":"false") << ")" << std::endl;
#endif
	return rt;
}

unsigned char RpcDeserializer::unpackByte()
{
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackByte(" << (unsigned int)(unsigned char)(*m_itr) << ")" << std::endl;
#endif
	return *m_itr++;
}

Index RpcDeserializer::unpackIndex()
{
	Index rt = unpackScalar<Index>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackIndex(" << rt << ")" << std::endl;
#endif
	return rt;
}

GlobalCounter RpcDeserializer::unpackGlobalCounter()
{
	GlobalCounter rt = unpackScalar<GlobalCounter>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackGlobalCounter(" << rt << ")" << std::endl;
#endif
	return rt;
}

unsigned int RpcDeserializer::unpackUint()
{
	unsigned int rt = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackUint(" << rt << ")" << std::endl;
#endif
	return rt;
}

int RpcDeserializer::unpackInt()
{
	int rt = unpackScalar<int32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackInt(" << rt << ")" << std::endl;
#endif
	return rt;
}

float RpcDeserializer::unpackFloat()
{
	return unpackScalar<float>( m_itr, m_end);
	float rt = unpackScalar<float>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackFloat(" << rt << ")" << std::endl;
#endif
	return rt;
}

double RpcDeserializer::unpackDouble()
{
	return unpackScalar<double>( m_itr, m_end);
	float rt = unpackScalar<double>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackDouble(" << rt << ")" << std::endl;
#endif
	return rt;
}

std::size_t RpcDeserializer::unpackSize()
{
	unsigned int rt = unpackScalar<uint32_t>( m_itr, m_end);
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackSize(" << rt << ")" << std::endl;
#endif
	return rt;
}

NumericVariant RpcDeserializer::unpackNumericVariant()
{
	NumericVariant::Type type = (NumericVariant::Type)unpackByte();
	switch (type)
	{
		case NumericVariant::Null: return NumericVariant();
		case NumericVariant::Int: return NumericVariant( unpackInt());
		case NumericVariant::UInt: return NumericVariant( unpackUint());
		case NumericVariant::Float: return NumericVariant( unpackDouble());
	}
	throw strus::runtime_error( _TXT("unknown type of numeric variant"));
}

analyzer::DocumentClass RpcDeserializer::unpackDocumentClass()
{
	analyzer::DocumentClass rt( unpackString());
	rt.setScheme( unpackString());
	rt.setEncoding( unpackString());
	return rt;
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

MetaDataRestrictionInterface::CompareOperator RpcDeserializer::unpackMetaDataRestrictionCompareOperator()
{
	return (MetaDataRestrictionInterface::CompareOperator)unpackByte();
}

bool RpcDeserializer::unpackCrc32()
{
#if STRUS_RPC_PROTOCOL_WITH_CRC32_CHECKSUM	
	uint32_t size = (m_end - m_start) - 4;
#ifdef STRUS_ALTERNATIVE_CHECK_SUM
	uint32_t crc = calcAlternativeCheckSum( m_start, size);
#else
	uint32_t crc = utils::Crc32::calc( m_start, size);
#endif
	char const* ee = m_end-4;
#ifdef STRUS_LOWLEVEL_DEBUG
	std::cerr << "unpackCrc32(" << crc << ") size=" << size << std::endl;
#endif
#ifdef STRUS_ALTERNATIVE_CHECK_SUM
	if (checkAlternativeCheckSum( crc, unpackScalar<uint32_t>( ee, m_end)))
	{
		return true;
	}
	else
	{
#ifdef STRUS_LOWLEVEL_DEBUG
		strus_hexdump( stderr, "CRC32 checksum failed", (const unsigned char*)m_start, (size_t)size);
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
	std::size_t size;
	unpackBuffer( buf, size);
	DatabaseCursorInterface::Slice rt( buf, size);
	return rt;
}

analyzer::Document RpcDeserializer::unpackAnalyzerDocument()
{
	analyzer::Document rt;
	rt.setSubDocumentTypeName( unpackString());
	std::size_t ii=0,size=unpackSize();
	for (; ii<size; ++ii)
	{
		std::string name = unpackString();
		std::string value = unpackString();
		rt.setAttribute( name, value);
	}
	for (ii=0,size=unpackSize(); ii<size; ++ii)
	{
		std::string name = unpackString();
		double value = unpackDouble();
		rt.setMetaData( name, value);
	}
	for (ii=0,size=unpackSize(); ii<size; ++ii)
	{
		std::string type = unpackString();
		std::string value = unpackString();
		unsigned int pos = unpackUint();
		rt.addSearchIndexTerm( type, value, pos);
	}
	for (ii=0,size=unpackSize(); ii<size; ++ii)
	{
		std::string type = unpackString();
		std::string value = unpackString();
		unsigned int pos = unpackUint();
		rt.addForwardIndexTerm( type, value, pos);
	}
	return rt;
}

analyzer::Query RpcDeserializer::unpackAnalyzerQuery()
{
	analyzer::Query rt;
	{
		std::size_t ii=0,size=unpackSize();
		for (; ii<size; ++ii)
		{
			analyzer::Query::Element::Type type = (analyzer::Query::Element::Type)unpackByte();
			switch (type)
			{
				case analyzer::Query::Element::MetaData:
				{
					analyzer::MetaData elem = unpackAnalyzerMetaData();
					unsigned int fieldNo = unpackIndex();
					unsigned int position = unpackIndex();
					rt.addMetaData( fieldNo, position, elem);
					break;
				}
				case analyzer::Query::Element::SearchIndexTerm:
				{
					analyzer::Term elem = unpackAnalyzerTerm();
					unsigned int fieldNo = unpackIndex();
					/*position*/(void)unpackIndex();
					rt.addSearchIndexTerm( fieldNo, elem);
					break;
				}
			}
		}
	}
	{
		std::size_t ii=0,size=unpackSize();
		for (; ii<size; ++ii)
		{
			analyzer::Query::Instruction::OpCode opCode = (analyzer::Query::Instruction::OpCode)unpackByte();
			switch (opCode)
			{
				case analyzer::Query::Instruction::PushMetaData:
					rt.pushMetaDataOperand( unpackIndex());
					break;
				case analyzer::Query::Instruction::PushSearchIndexTerm:
					rt.pushSearchIndexTermOperand( unpackIndex());
					break;
				case analyzer::Query::Instruction::Operator:
				{
					unsigned int operatorId = unpackIndex();
					unsigned int nofOperands = unpackIndex();
					rt.pushOperator( operatorId, nofOperands);
					break;
				}
			}
		}
	}
	return rt;
}

analyzer::Attribute RpcDeserializer::unpackAnalyzerAttribute()
{
	std::string name = unpackString();
	std::string value = unpackString();
	return analyzer::Attribute( name, value);
}

analyzer::MetaData RpcDeserializer::unpackAnalyzerMetaData()
{
	std::string name = unpackString();
	NumericVariant value = unpackNumericVariant();
	return analyzer::MetaData( name, value);
}

analyzer::Term RpcDeserializer::unpackAnalyzerTerm()
{
	std::string type = unpackString();
	std::string value = unpackString();
	unsigned int pos = (unsigned int)unpackIndex();
	return analyzer::Term( type, value, pos);
}

analyzer::TermArray RpcDeserializer::unpackAnalyzerTermArray()
{
	analyzer::TermArray rt;
	std::size_t ii = 0, size = unpackSize();
	for (; ii<size; ++ii)
	{
		rt.push_back( unpackAnalyzerTerm());
	}
	return rt;
}

analyzer::Token RpcDeserializer::unpackAnalyzerToken()
{
	unsigned int ordpos = unpackUint();
	unsigned int origseg = unpackUint();
	unsigned int origpos = unpackUint();
	unsigned int origsize = unpackUint();
	return analyzer::Token( ordpos, origseg, origpos, origsize);
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
	return analyzer::PatternLexem( id, ordpos, origseg, origpos, origsize);
}

analyzer::PatternLexerOptions RpcDeserializer::unpackAnalyzerPatternLexerOptions()
{
	analyzer::PatternLexerOptions rt;
	std::size_t ii = 0, size = unpackSize();
	for (; ii < size; ++ii)
	{
		rt( unpackString());
	}
	return rt;
}

analyzer::PatternMatcherOptions RpcDeserializer::unpackAnalyzerPatternMatcherOptions()
{
	analyzer::PatternMatcherOptions rt;
	std::size_t ii = 0, size = unpackSize();
	for (; ii < size; ++ii)
	{
		rt( unpackString(), unpackDouble());
	}
	return rt;
}

analyzer::TokenMarkup RpcDeserializer::unpackAnalyzerTokenMarkup()
{
	analyzer::TokenMarkup rt( unpackString());
	std::size_t ii = 0, size = unpackSize();
	for (; ii < size; ++ii)
	{
		rt( unpackString(), unpackString());
	}
	return rt;
}

analyzer::PatternMatcherResult RpcDeserializer::unpackAnalyzerPatternMatcherResult()
{
	const char* name( unpackConstCharp());
	unsigned int ordpos = unpackUint();
	unsigned int start_origseg = unpackUint();
	unsigned int start_origpos = unpackUint();
	unsigned int end_origseg = unpackUint();
	unsigned int end_origpos = unpackUint();

	std::vector<analyzer::PatternMatcherResult::Item> itemlist;
	std::size_t ii = 0, size = unpackSize();
	for (; ii < size; ++ii)
	{
		analyzer::PatternMatcherResult::Item item( unpackConstCharp(), unpackUint(), unpackUint(), unpackUint(), unpackUint(), unpackUint(), unpackDouble());
		itemlist.push_back( item);
	}
	analyzer::PatternMatcherResult rt( name, ordpos, start_origseg, start_origpos, end_origseg, end_origpos, itemlist);
	return rt;
}

analyzer::PatternMatcherStatistics RpcDeserializer::unpackAnalyzerPatternMatcherStatistics()
{
	analyzer::PatternMatcherStatistics rt;
	std::size_t ii = 0, size = unpackSize();
	for (; ii < size; ++ii)
	{
		rt.define( unpackConstCharp(), unpackDouble());
	}
	return rt;
}

analyzer::SegmenterOptions RpcDeserializer::unpackSegmenterOptions()
{
	analyzer::SegmenterOptions rt;
	std::size_t ii = 0, size = unpackSize();
	for (; ii < size; ++ii)
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
	std::size_t ii=0,size=unpackSize();
	for (; ii<size; ++ii)
	{
		summaryElements.push_back( unpackSummaryElement());
	}
	return ResultDocument( weightedDocument, summaryElements);
}

QueryResult RpcDeserializer::unpackQueryResult()
{
	unsigned int pass = unpackByte();
	unsigned int nofDocumentsRanked = unpackIndex();
	unsigned int nofDocumentsVisited = unpackIndex();
	std::size_t ii=0,size=unpackSize();
	std::vector<ResultDocument> ranks;
	for (; ii<size; ++ii)
	{
		ranks.push_back( unpackResultDocument());
	}
	return QueryResult( pass, nofDocumentsRanked, nofDocumentsVisited, ranks);
}

QueryEvalInterface::FeatureParameter RpcDeserializer::unpackFeatureParameter()
{
	std::string parameterName = unpackString();
	std::string featureSet = unpackString();
	return QueryEvalInterface::FeatureParameter( parameterName, featureSet);
}

StorageClientInterface::DocumentStatisticsType RpcDeserializer::unpackDocumentStatisticsType()
{
	return (StorageClientInterface::DocumentStatisticsType)unpackByte();
}

StatisticsProcessorInterface::BuilderOptions RpcDeserializer::unpackStatisticsProcessorBuilderOptions()
{
	unsigned int maxBlockSize = unpackUint();
	typedef StatisticsProcessorInterface::BuilderOptions::Set Set;
	Set set = (Set)unpackByte();
	return StatisticsProcessorInterface::BuilderOptions( set, maxBlockSize);
}

StatisticsViewerInterface::DocumentFrequencyChange RpcDeserializer::unpackStatisticsViewerDocumentFrequencyChange()
{
	typedef StatisticsViewerInterface::DocumentFrequencyChange DocumentFrequencyChange;
	DocumentFrequencyChange rt;
	rt.type = unpackConstCharp();
	rt.value = unpackConstCharp();
	rt.increment = unpackInt();
	return rt;
}

QueryProcessorInterface::FunctionType RpcDeserializer::unpackQueryProcessorFunctionType()
{
	return (QueryProcessorInterface::FunctionType)unpackByte();
}

TextProcessorInterface::FunctionType RpcDeserializer::unpackTextProcessorFunctionType()
{
	return (TextProcessorInterface::FunctionType)unpackByte();
}

PostingJoinOperatorInterface::Description RpcDeserializer::unpackPostingJoinOperatorDescription()
{
	return PostingJoinOperatorInterface::Description( unpackString());
}

FunctionDescription RpcDeserializer::unpackFunctionDescription()
{
	FunctionDescription rt( unpackString());
	unsigned int ii=0, nn=unpackSize();
	for (; ii<nn; ++ii)
	{
		FunctionDescription::Parameter::Type type = (FunctionDescription::Parameter::Type)unpackByte();
		std::string name( unpackString());
		std::string text( unpackString());
		std::string domain( unpackString());
		rt( type, name, text, domain);
	}
	return rt;
}

VectorStorageSearchInterface::Result RpcDeserializer::unpackVectorStorageSearchResult()
{
	Index featidx = unpackIndex();
	double weight = unpackDouble();
	return VectorStorageSearchInterface::Result( featidx, weight);
}


