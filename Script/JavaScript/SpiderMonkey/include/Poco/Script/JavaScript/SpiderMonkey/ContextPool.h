//
// ContextPool.h
//
// $Id$
//
// Library: JavaScript
// Package: SpiderMonkey
// Module:  PooledContext
//
// Definition of ContextPool.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// 3. Redistributions in any form must be accompanied by information on
//    how to obtain complete source code for this software and any
//    accompanying software that uses this software.  The source code
//    must either be included in the distribution or be available for no
//    more than the cost of distribution plus a nominal fee, and must be
//    freely redistributable under reasonable conditions.  For an
//    executable file, complete source code means the source code for all
//    modules it contains.  It does not include source code for modules or
//    files that typically accompany the major components of the operating
//    system on which the executable file runs.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//


#ifndef SpiderMonkey_ContextPool_INCLUDED
#define SpiderMonkey_ContextPool_INCLUDED

#include "Poco/Script/JavaScript/SpiderMonkey/SpiderMonkey.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"

#include <vector>

namespace Poco {
namespace Script {
namespace JavaScript {
namespace SpiderMonkey {

class Runtime;
class Context;

class ContextPool
  /// Class that manages a pool of Context objects
{
public:
  ContextPool(SharedPtr<Runtime> rt, int size);
    /// Constructor
  
  
  virtual ~ContextPool();
    /// Destructor
 
  
  SharedPtr<Context> getContext();
    /// Returns a Context from the pool. When no free context is found, 
    /// it will create a new Context and store it in the pool
 

private:

  SharedPtr<Runtime> _rt;
  
  
	int _size;


	std::vector<SharedPtr<Context> > _contexts;

  
  static Mutex _poolMutex;
}; 

} } } } // namespace Poco::Script::JavaScript::SpiderMonkey


#endif
