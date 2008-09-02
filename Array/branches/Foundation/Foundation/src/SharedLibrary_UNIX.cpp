//
// SharedLibrary_UNIX.cpp
//
// $Id: //poco/svn/Foundation/src/SharedLibrary_UNIX.cpp#3 $
//
// Library: Foundation
// Package: SharedLibrary
// Module:  SharedLibrary
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/SharedLibrary_UNIX.h"
#include "Poco/Exception.h"
#include <dlfcn.h>


// Note: cygwin is missing RTLD_LOCAL, set it to 0
#if defined(__CYGWIN__) && !defined(RTLD_LOCAL)
#define RTLD_LOCAL 0
#endif


namespace Poco {


FastMutex SharedLibraryImpl::_mutex;


SharedLibraryImpl::SharedLibraryImpl()
{
	_handle = 0;
}


SharedLibraryImpl::~SharedLibraryImpl()
{
}


void SharedLibraryImpl::loadImpl(const std::string& path)
{
	FastMutex::ScopedLock lock(_mutex);

	if (_handle) throw LibraryAlreadyLoadedException(path);
	_handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
	if (!_handle)
	{
		const char* err = dlerror();
		throw LibraryLoadException(err ? std::string(err) : path);
	}
	_path = path;
}


void SharedLibraryImpl::unloadImpl()
{
	FastMutex::ScopedLock lock(_mutex);

	if (_handle)
	{
		dlclose(_handle);
		_handle = 0;
	}
}


bool SharedLibraryImpl::isLoadedImpl() const
{
	return _handle != 0; 
}


void* SharedLibraryImpl::findSymbolImpl(const std::string& name)
{
	FastMutex::ScopedLock lock(_mutex);

	void* result = 0;
	if (_handle)
	{
		result = dlsym(_handle, name.c_str());
	}
	return result;
}


const std::string& SharedLibraryImpl::getPathImpl() const
{
	return _path;
}


std::string SharedLibraryImpl::suffixImpl()
{
#if defined(__APPLE__)
	#if defined(_DEBUG)
		return "d.dylib";
	#else
		return ".dylib";
	#endif
#elif defined(hpux) || defined(_hpux)
	#if defined(_DEBUG)
		return "d.sl";
	#else
		return ".sl";
	#endif
#elif defined(__CYGWIN__)
	#if defined(_DEBUG)
		return "d.dll";
	#else
		return ".dll";
	#endif
#else
	#if defined(_DEBUG)
		return "d.so";
	#else
		return ".so";
	#endif
#endif
}


} // namespace Poco
