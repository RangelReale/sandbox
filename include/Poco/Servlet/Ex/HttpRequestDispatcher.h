//
// HttpRequestDispatcher.h
//
//
// Library: ServletEx
// Package: Http
// Module:  HttpRequestDispatcher
//
// Definition of the HttpRequestDispatcher class.
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


#ifndef ServletEx_Http_HttpRequestDispatcher_INCLUDED
#define ServletEx_Http_HttpRequestDispatcher_INCLUDED


#include "Poco/Servlet/ServletBase.h"
#include "Poco/Servlet/Servlet.h"
#include "Poco/Servlet/RequestDispatcher.h"
#include "Poco/Servlet/ServletRequest.h"
#include "Poco/Servlet/HttpServletRequest.h"
#include "Poco/Servlet/ServletResponse.h"
#include "Poco/Servlet/HttpServletResponse.h"
#include "Poco/Servlet/Ex/HttpServletDispatcher.h"


namespace Poco {
namespace Servlet {
namespace Ex {


class Servlet_API HttpRequestDispatcher : public RequestDispatcher
	/// Basic implementation of the RequestDispatcher. This implementation
	/// only forwards the request/response pair to their destination.
	///
	/// For request preprocessing and/or SSI functionality, an implmentation
	/// should inherit from this class and override forwardImpl and includeImpl 
	/// member functions.
	/// See RequestDispatcher documentation for details on forward/include
	/// functionality.
{
public:
	HttpRequestDispatcher(HttpServletDispatcher& dispatcher, const std::string& path);
		/// Creates RequestDispatcher.

	virtual ~HttpRequestDispatcher();
		/// Destroys RequestDispatcher.

	void forward(ServletRequest& request, ServletResponse& response);
		/// Forwards the request. 
		/// See RequestDispatcher::forward documentation for details on forward functionality.

	void include(ServletRequest& request, ServletResponse& response);
		/// Forwards the request. 
		/// See RequestDispatcher::include documentation for details on include functionality.

	const std::string& path() const;

private:
	
	HttpServletDispatcher& _dispatcher;
	std::string            _path;
};


///
/// inlines
///


inline const std::string& HttpRequestDispatcher::path() const
{
	return _path;
}


} } } // namespace Poco::Servlet::Ex


#endif //ServletEx_Http_HttpRequestDispatcher_INCLUDED
