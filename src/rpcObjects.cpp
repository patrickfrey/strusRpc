/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2013,2014 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
*/
#include "rpcObjects.hpp"

using namespace strus;

Index AttributeReaderImpl::elementHandle( const char* p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packCharp( p1);
	msg.packCrc32();
}

void AttributeReaderImpl::skipDoc( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
}

std::string AttributeReaderImpl::getValue( const Index& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
}

bool DatabaseBackupCursorImpl::fetch( const char*& p1, std::size_t& p2, const char*& p3, std::size_t& p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
}

void DatabaseClientImpl::close( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
}

DatabaseTransactionInterface* DatabaseClientImpl::createTransaction( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
}

DatabaseCursorInterface* DatabaseClientImpl::createCursor( const DatabaseOptions& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	PACK_UNKNOWN( "DatabaseOptions" p1);
	msg.packCrc32();
}

DatabaseBackupCursorInterface* DatabaseClientImpl::createBackupCursor( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createBackupCursor);
	msg.packCrc32();
}

void DatabaseClientImpl::writeImm( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_writeImm);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
}

void DatabaseClientImpl::removeImm( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeImm);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

bool DatabaseClientImpl::readValue( const char* p1, std::size_t p2, std::string& p3, const DatabaseOptions& p4) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_readValue);
	msg.packBuffer( p1, p2);
	PACK_UNKNOWN( "DatabaseOptions" p4);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekUpperBound( const char* p1, std::size_t p2, std::size_t p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekUpperBound);
	msg.packBuffer( p1, p2);
	msg.packSize( p3);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekFirst( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekFirst);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekLast( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekLast);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekNext( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekNext);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::seekPrev( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_seekPrev);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::key( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_key);
	msg.packCrc32();
}

DatabaseCursorInterface::Slice DatabaseCursorImpl::value( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_value);
	msg.packCrc32();
}

DatabaseClientInterface* DatabaseImpl::createClient( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	msg.packCrc32();
}

void DatabaseImpl::createDatabase( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDatabase);
	msg.packString( p1);
	msg.packCrc32();
}

void DatabaseImpl::restoreDatabase( const std::string& p1, DatabaseBackupCursorInterface* p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_restoreDatabase);
	msg.packString( p1);
	const DatabaseBackupCursorImpl* impl_p2 = dynamic_cast<const DatabaseBackupCursorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

void DatabaseImpl::destroyDatabase( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_destroyDatabase);
	msg.packString( p1);
	msg.packCrc32();
}

const char* DatabaseImpl::getConfigDescription( DatabaseInterface::ConfigType p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	PACK_UNKNOWN( "DatabaseInterface::ConfigType" p1);
	msg.packCrc32();
}

const char** DatabaseImpl::getConfigParameters( DatabaseInterface::ConfigType p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	PACK_UNKNOWN( "DatabaseInterface::ConfigType" p1);
	msg.packCrc32();
}

DatabaseCursorInterface* DatabaseTransactionImpl::createCursor( const DatabaseOptions& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createCursor);
	PACK_UNKNOWN( "DatabaseOptions" p1);
	msg.packCrc32();
}

void DatabaseTransactionImpl::write( const char* p1, std::size_t p2, const char* p3, std::size_t p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_write);
	msg.packBuffer( p1, p2);
	msg.packBuffer( p3, p4);
	msg.packCrc32();
}

void DatabaseTransactionImpl::remove( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_remove);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

void DatabaseTransactionImpl::removeSubTree( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_removeSubTree);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

void DatabaseTransactionImpl::commit( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
}

void DatabaseTransactionImpl::rollback( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
}

Index DocnoRangeAllocatorImpl::allocDocnoRange( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_allocDocnoRange);
	msg.packIndex( p1);
	msg.packCrc32();
}

bool DocnoRangeAllocatorImpl::deallocDocnoRange( const Index& p1, const Index& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deallocDocnoRange);
	msg.packIndex( p1);
	msg.packIndex( p2);
	msg.packCrc32();
}

void DocumentAnalyzerInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
}

bool DocumentAnalyzerInstanceImpl::analyzeNext( analyzer::Document& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzeNext);
	msg.packCrc32();
}

void DocumentAnalyzerImpl::addSearchIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	PACK_UNKNOWN( "TokenizerConfig" p3);
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		PACK_UNKNOWN( "NormalizerConfig" p4[ii]);
	}
	PACK_UNKNOWN( "DocumentAnalyzerInterface::FeatureOptions" p5);
	msg.packCrc32();
}

void DocumentAnalyzerImpl::addForwardIndexFeature( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4, const DocumentAnalyzerInterface::FeatureOptions& p5)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexFeature);
	msg.packString( p1);
	msg.packString( p2);
	PACK_UNKNOWN( "TokenizerConfig" p3);
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		PACK_UNKNOWN( "NormalizerConfig" p4[ii]);
	}
	PACK_UNKNOWN( "DocumentAnalyzerInterface::FeatureOptions" p5);
	msg.packCrc32();
}

void DocumentAnalyzerImpl::defineMetaData( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaData);
	msg.packString( p1);
	msg.packString( p2);
	PACK_UNKNOWN( "TokenizerConfig" p3);
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		PACK_UNKNOWN( "NormalizerConfig" p4[ii]);
	}
	msg.packCrc32();
}

void DocumentAnalyzerImpl::defineAttribute( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineAttribute);
	msg.packString( p1);
	msg.packString( p2);
	PACK_UNKNOWN( "TokenizerConfig" p3);
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		PACK_UNKNOWN( "NormalizerConfig" p4[ii]);
	}
	msg.packCrc32();
}

void DocumentAnalyzerImpl::defineSubDocument( const std::string& p1, const std::string& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubDocument);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

analyzer::Document DocumentAnalyzerImpl::analyze( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyze);
	msg.packString( p1);
	msg.packCrc32();
}

DocumentAnalyzerInstanceInterface* DocumentAnalyzerImpl::createInstance( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
}

void ForwardIteratorImpl::skipDoc( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
}

Index ForwardIteratorImpl::skipPos( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
}

std::string ForwardIteratorImpl::fetch( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_fetch);
	msg.packCrc32();
}

Index InvAclIteratorImpl::skipDoc( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
}

bool MetaDataReaderImpl::hasElement( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_hasElement);
	msg.packString( p1);
	msg.packCrc32();
}

Index MetaDataReaderImpl::elementHandle( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_elementHandle);
	msg.packString( p1);
	msg.packCrc32();
}

Index MetaDataReaderImpl::nofElements( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nofElements);
	msg.packCrc32();
}

void MetaDataReaderImpl::skipDoc( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
}

ArithmeticVariant MetaDataReaderImpl::getValue( const Index& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getValue);
	msg.packIndex( p1);
	msg.packCrc32();
}

const char* MetaDataReaderImpl::getType( const Index& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getType);
	msg.packIndex( p1);
	msg.packCrc32();
}

const char* MetaDataReaderImpl::getName( const Index& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getName);
	msg.packIndex( p1);
	msg.packCrc32();
}

NormalizerInterface* NormalizerConstructorImpl::create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_create);
	packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	const TextProcessorImpl* impl_p2 = dynamic_cast<const TextProcessorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

std::string NormalizerInstanceImpl::normalize( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_normalize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

NormalizerInstanceInterface* NormalizerImpl::createInstance( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
}

void PeerStorageTransactionImpl::updateNofDocumentsInsertedChange( const GlobalCounter& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateNofDocumentsInsertedChange);
	msg.packGlobalCounter( p1);
	msg.packCrc32();
}

void PeerStorageTransactionImpl::updateDocumentFrequencyChange( const char* p1, const char* p2, const GlobalCounter& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_updateDocumentFrequencyChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packGlobalCounter( p3);
	msg.packCrc32();
}

void PeerStorageTransactionImpl::commit( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
}

void PeerStorageTransactionImpl::rollback( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
}

Index PostingIteratorImpl::skipDoc( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipDoc);
	msg.packIndex( p1);
	msg.packCrc32();
}

Index PostingIteratorImpl::skipPos( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_skipPos);
	msg.packIndex( p1);
	msg.packCrc32();
}

const char* PostingIteratorImpl::featureid( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureid);
	msg.packCrc32();
}

const std::vector<PostingIteratorInterface<*> > PostingIteratorImpl::subExpressions( bool p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_subExpressions);
	msg.packBool( p1);
	msg.packCrc32();
}

GlobalCounter PostingIteratorImpl::documentFrequency( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentFrequency);
	msg.packCrc32();
}

unsigned int PostingIteratorImpl::frequency( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_frequency);
	msg.packCrc32();
}

Index PostingIteratorImpl::docno( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_docno);
	msg.packCrc32();
}

Index PostingIteratorImpl::posno( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_posno);
	msg.packCrc32();
}

PostingIteratorInterface* PostingJoinOperatorImpl::createResultIterator( const std::vector<Reference<PostingIteratorInterface> >& p1, int p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createResultIterator);
	packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		PACK_UNKNOWN( "Reference<PostingIteratorInterface> " p1[ii]);
	}
	msg.packInt( p2);
	msg.packCrc32();
}

void QueryAnalyzerImpl::definePhraseType( const std::string& p1, const std::string& p2, const TokenizerConfig& p3, const std::vector<NormalizerConfig>& p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePhraseType);
	msg.packString( p1);
	msg.packString( p2);
	PACK_UNKNOWN( "TokenizerConfig" p3);
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		PACK_UNKNOWN( "NormalizerConfig" p4[ii]);
	}
	msg.packCrc32();
}

std::vector<analyzer::Term> QueryAnalyzerImpl::analyzePhrase( const std::string& p1, const std::string& p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_analyzePhrase);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void QueryEvalImpl::addTerm( const std::string& p1, const std::string& p2, const std::string& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
}

void QueryEvalImpl::addSelectionFeature( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSelectionFeature);
	msg.packString( p1);
	msg.packCrc32();
}

void QueryEvalImpl::addRestrictionFeature( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addRestrictionFeature);
	msg.packString( p1);
	msg.packCrc32();
}

void QueryEvalImpl::addSummarizer( const std::string& p1, const std::string& p2, const SummarizerConfig& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSummarizer);
	msg.packString( p1);
	msg.packString( p2);
	PACK_UNKNOWN( "SummarizerConfig" p3);
	msg.packCrc32();
}

void QueryEvalImpl::addWeightingFunction( const std::string& p1, const WeightingConfig& p2, const std::vector<std::string>& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addWeightingFunction);
	msg.packString( p1);
	PACK_UNKNOWN( "WeightingConfig" p2);
	packSize( p3.size());
	for (unsigned int ii=0; ii < p3.size(); ++ii) {
		msg.packString( p3[ii]);
	}
	msg.packCrc32();
}

QueryInterface* QueryEvalImpl::createQuery( const StorageClientInterface* p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createQuery);
	const StorageClientImpl* impl_p1 = dynamic_cast<const StorageClientImpl*>(p1);
	if (!impl_p1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p1->classId(), impl_p1->objId());
	msg.packCrc32();
}

void QueryImpl::pushTerm( const std::string& p1, const std::string& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void QueryImpl::pushExpression( const std::string& p1, std::size_t p2, int p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushExpression);
	msg.packString( p1);
	msg.packSize( p2);
	msg.packInt( p3);
	msg.packCrc32();
}

void QueryImpl::pushDuplicate( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_pushDuplicate);
	msg.packCrc32();
}

void QueryImpl::attachVariable( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_attachVariable);
	msg.packString( p1);
	msg.packCrc32();
}

void QueryImpl::defineFeature( const std::string& p1, float p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineFeature);
	msg.packString( p1);
	msg.packFloat( p2);
	msg.packCrc32();
}

void QueryImpl::defineMetaDataRestriction( QueryInterface::CompareOperator p1, const std::string& p2, const ArithmeticVariant& p3, bool p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineMetaDataRestriction);
	PACK_UNKNOWN( "QueryInterface::CompareOperator" p1);
	msg.packString( p2);
	msg.packArithmeticVariant( p3);
	msg.packBool( p4);
	msg.packCrc32();
}

void QueryImpl::setMaxNofRanks( std::size_t p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMaxNofRanks);
	msg.packSize( p1);
	msg.packCrc32();
}

void QueryImpl::setMinRank( std::size_t p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMinRank);
	msg.packSize( p1);
	msg.packCrc32();
}

void QueryImpl::setUserName( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserName);
	msg.packString( p1);
	msg.packCrc32();
}

std::vector<ResultDocument> QueryImpl::evaluate( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_evaluate);
	msg.packCrc32();
}

void QueryProcessorImpl::definePostingJoinOperator( const std::string& p1, PostingJoinOperatorInterface* p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_definePostingJoinOperator);
	msg.packString( p1);
	const PostingJoinOperatorImpl* impl_p2 = dynamic_cast<const PostingJoinOperatorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

const PostingJoinOperatorInterface* QueryProcessorImpl::getPostingJoinOperator( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getPostingJoinOperator);
	msg.packString( p1);
	msg.packCrc32();
}

void QueryProcessorImpl::defineWeightingFunction( const std::string& p1, WeightingFunctionInterface* p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineWeightingFunction);
	msg.packString( p1);
	const WeightingFunctionImpl* impl_p2 = dynamic_cast<const WeightingFunctionImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

const WeightingFunctionInterface* QueryProcessorImpl::getWeightingFunction( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getWeightingFunction);
	msg.packString( p1);
	msg.packCrc32();
}

void QueryProcessorImpl::defineSummarizerFunction( const std::string& p1, SummarizerFunctionInterface* p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSummarizerFunction);
	msg.packString( p1);
	const SummarizerFunctionImpl* impl_p2 = dynamic_cast<const SummarizerFunctionImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

const SummarizerFunctionInterface* QueryProcessorImpl::getSummarizerFunction( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummarizerFunction);
	msg.packString( p1);
	msg.packCrc32();
}

void SegmenterInstanceImpl::putInput( const char* p1, std::size_t p2, bool p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_putInput);
	msg.packBuffer( p1, p2);
	msg.packBool( p3);
	msg.packCrc32();
}

bool SegmenterInstanceImpl::getNext( int& p1, SegmenterPosition& p2, const char*& p3, std::size_t& p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNext);
	msg.packCrc32();
}

void SegmenterImpl::defineSelectorExpression( int p1, const std::string& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSelectorExpression);
	msg.packInt( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void SegmenterImpl::defineSubSection( int p1, int p2, const std::string& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineSubSection);
	msg.packInt( p1);
	msg.packInt( p2);
	msg.packString( p3);
	msg.packCrc32();
}

SegmenterInstanceInterface* SegmenterImpl::createInstance( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::addElement( const std::string& p1, const std::string& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::alterElement( const std::string& p1, const std::string& p2, const std::string& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_alterElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packString( p3);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::renameElement( const std::string& p1, const std::string& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_renameElement);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::deleteElement( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteElement);
	msg.packString( p1);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::clearElement( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_clearElement);
	msg.packString( p1);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::commit( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
}

void StorageAlterMetaDataTableImpl::rollback( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
}

void StorageClientImpl::close( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_close);
	msg.packCrc32();
}

PostingIteratorInterface* StorageClientImpl::createTermPostingIterator( const std::string& p1, const std::string& p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTermPostingIterator);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

ForwardIteratorInterface* StorageClientImpl::createForwardIterator( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createForwardIterator);
	msg.packString( p1);
	msg.packCrc32();
}

InvAclIteratorInterface* StorageClientImpl::createInvAclIterator( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInvAclIterator);
	msg.packString( p1);
	msg.packCrc32();
}

GlobalCounter StorageClientImpl::globalNofDocumentsInserted( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalNofDocumentsInserted);
	msg.packCrc32();
}

Index StorageClientImpl::localNofDocumentsInserted( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localNofDocumentsInserted);
	msg.packCrc32();
}

GlobalCounter StorageClientImpl::globalDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_globalDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

Index StorageClientImpl::localDocumentFrequency( const std::string& p1, const std::string& p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_localDocumentFrequency);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

Index StorageClientImpl::maxDocumentNumber( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_maxDocumentNumber);
	msg.packCrc32();
}

Index StorageClientImpl::documentNumber( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_documentNumber);
	msg.packString( p1);
	msg.packCrc32();
}

MetaDataReaderInterface* StorageClientImpl::createMetaDataReader( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createMetaDataReader);
	msg.packCrc32();
}

AttributeReaderInterface* StorageClientImpl::createAttributeReader( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAttributeReader);
	msg.packCrc32();
}

DocnoRangeAllocatorInterface* StorageClientImpl::createDocnoRangeAllocator( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocnoRangeAllocator);
	msg.packCrc32();
}

StorageTransactionInterface* StorageClientImpl::createTransaction( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
}

PeerStorageTransactionInterface* StorageClientImpl::createPeerStorageTransaction( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createPeerStorageTransaction);
	msg.packCrc32();
}

void StorageClientImpl::defineStoragePeerInterface( const StoragePeerInterface* p1, bool p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineStoragePeerInterface);
	const StoragePeerImpl* impl_p1 = dynamic_cast<const StoragePeerImpl*>(p1);
	if (!impl_p1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p1->classId(), impl_p1->objId());
	msg.packBool( p2);
	msg.packCrc32();
}

StorageDocumentInterface* StorageClientImpl::createDocumentChecker( const std::string& p1, const std::string& p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocumentChecker);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void StorageClientImpl::checkStorage( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_checkStorage);
	msg.packCrc32();
}

StorageDumpInterface* StorageClientImpl::createDump( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDump);
	msg.packCrc32();
}

void StorageDocumentImpl::addSearchIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addSearchIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
}

void StorageDocumentImpl::addForwardIndexTerm( const std::string& p1, const std::string& p2, const Index& p3)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addForwardIndexTerm);
	msg.packString( p1);
	msg.packString( p2);
	msg.packIndex( p3);
	msg.packCrc32();
}

void StorageDocumentImpl::setMetaData( const std::string& p1, const ArithmeticVariant& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setMetaData);
	msg.packString( p1);
	msg.packArithmeticVariant( p2);
	msg.packCrc32();
}

void StorageDocumentImpl::setAttribute( const std::string& p1, const std::string& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setAttribute);
	msg.packString( p1);
	msg.packString( p2);
	msg.packCrc32();
}

void StorageDocumentImpl::setUserAccessRight( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_setUserAccessRight);
	msg.packString( p1);
	msg.packCrc32();
}

void StorageDocumentImpl::done( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_done);
	msg.packCrc32();
}

bool StorageDumpImpl::nextChunk( const char*& p1, std::size_t& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_nextChunk);
	msg.packCrc32();
}

StorageClientInterface* StorageImpl::createClient( const std::string& p1, DatabaseClientInterface* p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClient);
	msg.packString( p1);
	const DatabaseClientImpl* impl_p2 = dynamic_cast<const DatabaseClientImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

void StorageImpl::createStorage( const std::string& p1, DatabaseClientInterface* p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createStorage);
	msg.packString( p1);
	const DatabaseClientImpl* impl_p2 = dynamic_cast<const DatabaseClientImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

StorageAlterMetaDataTableInterface* StorageImpl::createAlterMetaDataTable( DatabaseClientInterface* p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createAlterMetaDataTable);
	const DatabaseClientImpl* impl_p1 = dynamic_cast<const DatabaseClientImpl*>(p1);
	if (!impl_p1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p1->classId(), impl_p1->objId());
	msg.packCrc32();
}

const char* StorageImpl::getConfigDescription( StorageInterface::ConfigType p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigDescription);
	PACK_UNKNOWN( "StorageInterface::ConfigType" p1);
	msg.packCrc32();
}

const char** StorageImpl::getConfigParameters( StorageInterface::ConfigType p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getConfigParameters);
	PACK_UNKNOWN( "StorageInterface::ConfigType" p1);
	msg.packCrc32();
}

StoragePeerTransactionInterface* StoragePeerImpl::createTransaction( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createTransaction);
	msg.packCrc32();
}

void StoragePeerTransactionImpl::populateNofDocumentsInsertedChange( int p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateNofDocumentsInsertedChange);
	msg.packInt( p1);
	msg.packCrc32();
}

void StoragePeerTransactionImpl::populateDocumentFrequencyChange( const char* p1, const char* p2, int p3, bool p4)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_populateDocumentFrequencyChange);
	msg.packCharp( p1);
	msg.packCharp( p2);
	msg.packInt( p3);
	msg.packBool( p4);
	msg.packCrc32();
}

void StoragePeerTransactionImpl::try_commit( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_try_commit);
	msg.packCrc32();
}

void StoragePeerTransactionImpl::final_commit( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_final_commit);
	msg.packCrc32();
}

void StoragePeerTransactionImpl::rollback( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
}

StorageDocumentInterface* StorageTransactionImpl::createDocument( const std::string& p1, const Index& p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createDocument);
	msg.packString( p1);
	msg.packIndex( p2);
	msg.packCrc32();
}

void StorageTransactionImpl::deleteDocument( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteDocument);
	msg.packString( p1);
	msg.packCrc32();
}

void StorageTransactionImpl::deleteUserAccessRights( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_deleteUserAccessRights);
	msg.packString( p1);
	msg.packCrc32();
}

void StorageTransactionImpl::commit( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_commit);
	msg.packCrc32();
}

void StorageTransactionImpl::rollback( )
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_rollback);
	msg.packCrc32();
}

std::vector<SummarizerClosureInterface::SummaryElement> SummarizerClosureImpl::getSummary( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getSummary);
	msg.packIndex( p1);
	msg.packCrc32();
}

const char** SummarizerFunctionImpl::numericParameterNames( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_numericParameterNames);
	msg.packCrc32();
}

const char** SummarizerFunctionImpl::textualParameterNames( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_textualParameterNames);
	msg.packCrc32();
}

const char** SummarizerFunctionImpl::featureParameterClassNames( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_featureParameterClassNames);
	msg.packCrc32();
}

SummarizerClosureInterface* SummarizerFunctionImpl::createClosure( const StorageClientInterface* p1, const QueryProcessorInterface* p2, MetaDataReaderInterface* p3, const std::vector<SummarizerFunctionInterface::FeatureParameter>& p4, const std::vector<std::string>& p5, const std::vector<ArithmeticVariant>& p6) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClosure);
	const StorageClientImpl* impl_p1 = dynamic_cast<const StorageClientImpl*>(p1);
	if (!impl_p1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p1->classId(), impl_p1->objId());
	const QueryProcessorImpl* impl_p2 = dynamic_cast<const QueryProcessorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	const MetaDataReaderImpl* impl_p3 = dynamic_cast<const MetaDataReaderImpl*>(p3);
	if (!impl_p3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p3->classId(), impl_p3->objId());
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		PACK_UNKNOWN( "SummarizerFunctionInterface::FeatureParameter" p4[ii]);
	}
	packSize( p5.size());
	for (unsigned int ii=0; ii < p5.size(); ++ii) {
		msg.packString( p5[ii]);
	}
	packSize( p6.size());
	for (unsigned int ii=0; ii < p6.size(); ++ii) {
		msg.packArithmeticVariant( p6[ii]);
	}
	msg.packCrc32();
}

void TextProcessorImpl::addResourcePath( const std::string& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_addResourcePath);
	msg.packString( p1);
	msg.packCrc32();
}

std::string TextProcessorImpl::getResourcePath( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getResourcePath);
	msg.packString( p1);
	msg.packCrc32();
}

const TokenizerConstructorInterface* TextProcessorImpl::getTokenizer( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getTokenizer);
	msg.packString( p1);
	msg.packCrc32();
}

const NormalizerConstructorInterface* TextProcessorImpl::getNormalizer( const std::string& p1) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_getNormalizer);
	msg.packString( p1);
	msg.packCrc32();
}

void TextProcessorImpl::defineTokenizer( const std::string& p1, const TokenizerConstructorInterface* p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineTokenizer);
	msg.packString( p1);
	const TokenizerConstructorImpl* impl_p2 = dynamic_cast<const TokenizerConstructorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

void TextProcessorImpl::defineNormalizer( const std::string& p1, const NormalizerConstructorInterface* p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_defineNormalizer);
	msg.packString( p1);
	const NormalizerConstructorImpl* impl_p2 = dynamic_cast<const NormalizerConstructorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

TokenizerInterface* TokenizerConstructorImpl::create( const std::vector<std::string>& p1, const TextProcessorInterface* p2) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_create);
	packSize( p1.size());
	for (unsigned int ii=0; ii < p1.size(); ++ii) {
		msg.packString( p1[ii]);
	}
	const TextProcessorImpl* impl_p2 = dynamic_cast<const TextProcessorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	msg.packCrc32();
}

std::vector<analyzer::Token> TokenizerInstanceImpl::tokenize( const char* p1, std::size_t p2)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_tokenize);
	msg.packBuffer( p1, p2);
	msg.packCrc32();
}

bool TokenizerImpl::concatBeforeTokenize( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_concatBeforeTokenize);
	msg.packCrc32();
}

TokenizerInstanceInterface* TokenizerImpl::createInstance( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createInstance);
	msg.packCrc32();
}

float WeightingClosureImpl::call( const Index& p1)
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_call);
	msg.packIndex( p1);
	msg.packCrc32();
}

const char** WeightingFunctionImpl::numericParameterNames( ) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_numericParameterNames);
	msg.packCrc32();
}

WeightingClosureInterface* WeightingFunctionImpl::createClosure( const StorageClientInterface* p1, PostingIteratorInterface* p2, MetaDataReaderInterface* p3, const std::vector<ArithmeticVariant>& p4) const
{
	RcpMessage msg;
	msg.packObject( classId(), objId());
	msg.packByte( Method_createClosure);
	const StorageClientImpl* impl_p1 = dynamic_cast<const StorageClientImpl*>(p1);
	if (!impl_p1) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p1->classId(), impl_p1->objId());
	const PostingIteratorImpl* impl_p2 = dynamic_cast<const PostingIteratorImpl*>(p2);
	if (!impl_p2) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p2->classId(), impl_p2->objId());
	const MetaDataReaderImpl* impl_p3 = dynamic_cast<const MetaDataReaderImpl*>(p3);
	if (!impl_p3) throw std::runtime_error( "passing non RPC interface object in RPC call");
	msg.packObject( impl_p3->classId(), impl_p3->objId());
	packSize( p4.size());
	for (unsigned int ii=0; ii < p4.size(); ++ii) {
		msg.packArithmeticVariant( p4[ii]);
	}
	msg.packCrc32();
}

