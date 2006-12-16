//
// PocoServer.h
//
//
// Library: PocoServer
// Package: PocoServerCore
// Module:  PocoServer
//
// Definition of the PocoServer class.
//
// Copyright (c) 2006, Aleksandar Fabijanic and Contributors.
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


#ifndef PocoServer_INCLUDED
#define PocoServer_INCLUDED


#if defined(_WIN32) && defined(POCO_SERVER_DLL)
#	if defined(POCO_SERVER_EXPORTS)
#		define PocoServer_API __declspec(dllexport)
#	else
#		define PocoServer_API __declspec(dllimport)
#	endif
#else
#	define PocoServer_API
#endif


#include "Poco/Servlet/Ex/HttpServletDispatcher.h"
#include "Poco/Servlet/Ex/HttpServer.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include <vector>


namespace Poco {
namespace Servlet {
namespace PocoServer {


class PocoServer_API PocoServer : public Poco::Servlet::Ex::HttpServer
{
 public: 
	 PocoServer();
	 
	 PocoServer(const Poco::Servlet::Ex::HttpServerConfig& config
		 , Poco::Servlet::Ex::HttpServletDispatcher& dispatcher
		 , Poco::Logger* pLogger=0);

	 ~PocoServer();
	 void start();

private:
  Poco::Mutex _mutex;
};


} } } // namespace Poco::Servlet::PocoServer


#endif //PocoServer_INCLUDED
