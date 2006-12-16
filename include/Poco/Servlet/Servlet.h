//
// Servlet.h
//
//
// Library: Servlet
// Package: Servlet
// Module:  Servlet
//
// Definition of the Servlet class.
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
//
// The code in this file is derived from Apache Tomcat project
// Copyright (c) 2004 The Apache Software Foundation.
// http://www.apache.org/licenses/LICENSE-2.0
// 


#ifndef Servlet_Servlet_INCLUDED
#define Servlet_Servlet_INCLUDED


#include "Poco/Servlet/ServletException.h"
#include "Poco/Servlet/ServletConfig.h"
#include "Poco/Servlet/ServletRequest.h"
#include "Poco/Servlet/ServletResponse.h"
#include "Poco/Servlet/ServletBase.h"
#include <string>


namespace Poco {
namespace Servlet {


class Servlet_API Servlet 
	/// Defines methods that all servlets must implement.
	/// A servlet is a program that runs within a Web server. Servlets receive
	/// and respond to requests from Web clients, usually across HTTP. 
	/// 
	/// This interface defines methods to initialize a servlet, to service requests, and to
	/// remove a servlet from the server. These are known as life-cycle methods and are
	/// called in the following sequence:
	/// 1.The servlet is constructed, then initialized with the init method.
	/// 2.Any calls from clients to the service method are handled.
	/// 3.The servlet is taken out of service, then destroyed with the destroy method,
	/// then garbage collected and finalized.
	/// In addition to the life-cycle methods, this interface provides the 
	/// getServletConfig method, which the servlet can use to get any startup information, 
	/// and the getServletInfo method, which allows the servlet to return basic information
	/// about itself, such as author, version, and copyright.
	/// 
{
public: 
	Servlet();

	virtual ~Servlet();

	virtual void destroy() = 0;
	/// Called by the servlet container to indicate to a servlet that the servlet is being
	/// taken out of service. This method is only called once all threads within the
	/// servletís service method have exited or after a timeout period has passed.
	/// After the servlet container calls this method, it will not call the service
	/// method again on this servlet.

	virtual const ServletConfig& getServletConfig() const = 0;
	/// Returns a ServletConfig object, which contains initialization and startup
	/// parameters for this servlet. The ServletConfig object returned is the one
	/// passed to the init method.
	/// Implementations of this interface are responsible for storing the Servlet-
	/// Config object so that this method can return it. The GenericServlet class,
	/// which implements this interface, already does this.

	virtual std::string getServletInfo() const = 0;
	/// Returns information about the servlet, such as author, version, and copyright.
	/// The string that this method returns should be plain text.

	virtual void init(ServletConfig* config) = 0;
	/// Called by the servlet container to indicate to a servlet that the servlet is being
	/// placed into service.
	/// The servlet container calls the init method exactly once after instantiating
	/// the servlet. The init method must complete successfully before the servlet
	/// can receive any requests. The pointer to ServletConfig passed to this function shall
	/// be taken into ownership by the servlet and deleted upon servlet destruction.
	/// The servlet container cannot place the servlet into service if the init method
	/// 1. Throws a ServletException
	/// 2. Does not return within a time period defined by the web server

	virtual void service(ServletRequest& req, ServletResponse& res) = 0;
	/// Called by the servlet container to allow the servlet to respond to a request.
	/// This method is only called after the servletís init() method has completed
	/// successfully.
	/// The status code of the response always should be set for a servlet that throws
	/// or sends an error.
};


} } // namespace Poco::Servlet


#endif // Servlet_Servlet_INCLUDED
