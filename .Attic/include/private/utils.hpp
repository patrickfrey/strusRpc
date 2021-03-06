/*
 * Copyright (c) 2014 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Some utility functions that are centralized to control dependencies to boost
#ifndef _STRUS_UTILS_HPP_INCLUDED
#define _STRUS_UTILS_HPP_INCLUDED
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <stdint.h>	///... Needed by <boost/atomic.hpp> (!)
#include <boost/atomic.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/lockfree/policies.hpp>
#include <boost/thread/condition_variable.hpp> 

namespace strus {
namespace utils {

std::string tostring( int val);
unsigned int touint( const std::string& val);

template <class X>
class SharedPtr
	:public boost::shared_ptr<X>
{
public:
	SharedPtr( X* ptr)
		:boost::shared_ptr<X>(ptr){}
	SharedPtr( X* ptr, void (*Deleter)( X* ptr))
		:boost::shared_ptr<X>(ptr,Deleter){}
	SharedPtr( const SharedPtr& o)
		:boost::shared_ptr<X>(o){}
	SharedPtr()
		:boost::shared_ptr<X>(){}
};

template <class X>
class ScopedPtr
	:public boost::scoped_ptr<X>
{
public:
	ScopedPtr( X* ptr)
		:boost::scoped_ptr<X>(ptr){}
	ScopedPtr( const ScopedPtr& o)
		:boost::scoped_ptr<X>(o){}
	ScopedPtr()
		:boost::scoped_ptr<X>(){}
};

typedef boost::atomic<bool> AtomicBool;
typedef boost::mutex Mutex;
typedef boost::mutex::scoped_lock ScopedLock;
typedef boost::unique_lock<boost::mutex> UniqueLock;
typedef boost::condition_variable ConditionVariable;

template <class Task>
class Thread
	:public boost::thread
{
public:
	explicit Thread( Task* task)
		:boost::thread( boost::bind( &Task::run, task))
	{}
};

typedef boost::thread_group ThreadGroup;

template <class Element>
class LockFreeFixedSizeQueue
	:protected boost::lockfree::queue<Element,boost::lockfree::fixed_sized<true> >
{
	typedef boost::lockfree::queue<Element,boost::lockfree::fixed_sized<true> > Parent;

	LockFreeFixedSizeQueue( unsigned int size_)
		:Parent( size_){}

	bool push( const Element& element_)
	{
		 return bounded_push( element_);
	}
	bool pop( Element& element_)
	{
		 return pop( element_);
	}
};

}} //namespace
#endif


