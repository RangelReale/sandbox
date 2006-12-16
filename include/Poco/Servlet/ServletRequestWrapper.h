//
// ServletRequestWrapper.h
//
//
// Library: Servlet
// Package: Servlet
// Module:  ServletRequestWrapper
//
// Definition of the ServletRequestWrapper class.
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


#ifndef Servlet_ServletRequestWrapper_INCLUDED
#define Servlet_ServletRequestWrapper_INCLUDED


#include "ServletRequest.h"
#include <locale>
#include <vector>
#include <map>


namespace Poco {
namespace Servlet {


class Servlet_API ServletRequestWrapper : virtual public ServletRequest 
{
public:
	ServletRequestWrapper(ServletRequest& request);
		/// Creates ServletRequest wrapper. 

	virtual ~ServletRequestWrapper();
		/// Destroys ServletRequest wrapper. 

	virtual const ServletRequest* getRequest() const;
		/// Return the wrapped request object.
	
	virtual void setRequest(const ServletRequest& request);
		/// Sets the request object being wrapped. 

	virtual const Object* getAttribute(const std::string& name) const;
		/// The default behavior of this method is to call getAttribute(String name)
		/// on the wrapped request object.
    
	virtual std::vector<std::string> getAttributeNames() const;
		/// The default behavior of this method is to return getAttributeNames()
		/// on the wrapped request object.
    
	virtual std::string getCharacterEncoding() const;
		/// The default behavior of this method is to return getCharacterEncoding()
		/// on the wrapped request object.
	
	virtual void setCharacterEncoding(const std::string& enc);
		/// The default behavior of this method is to set the character encoding
		/// on the wrapped request object.
    
	virtual int getContentLength() const;
		/// The default behavior of this method is to return getContentLength()
		/// on the wrapped request object.
    
	virtual std::string getContentType() const;
		/// The default behavior of this method is to return getContentType()
		/// on the wrapped request object.

	virtual ServletInputStream& getInputStream();
		/// The default behavior of this method is to return getInputStream()
		/// on the wrapped request object.
     
	virtual std::string getParameter(const std::string& name) const;
		/// The default behavior of this method is to return getParameter(String name)
		/// on the wrapped request object.
    
	virtual Parameters getParameterMap() const;
		/// The default behavior of this method is to return getParameterMap()
		/// on the wrapped request object.
    
	virtual std::vector<std::string> getParameterNames() const;
		/// The default behavior of this method is to return getParameterNames()
		/// on the wrapped request object.
 
	virtual std::vector<std::string> getParameterValues(const std::string& name) const;
		/// The default behavior of this method is to return getParameterValues(string& name)
		/// on the wrapped request object.
    
	virtual std::string getProtocol() const;
		/// The default behavior of this method is to return getProtocol()
		/// on the wrapped request object.
 
	virtual std::string getScheme() const;
		/// The default behavior of this method is to return getScheme()
		/// on the wrapped request object.
    
	virtual std::string getServerName() const;
		/// The default behavior of this method is to return getServerName()
		/// on the wrapped request object.
    
	virtual int getServerPort() const;
		/// The default behavior of this method is to return getServerPort()
		/// on the wrapped request object.
    
	virtual const BufferedReader& getReader() const;
		/// The default behavior of this method is to return getReader()
		/// on the wrapped request object.
    
	virtual std::string getRemoteAddr() const;
		/// The default behavior of this method is to return getRemoteAddr()
		/// on the wrapped request object.

	virtual std::string getRemoteHost() const;
		/// The default behavior of this method is to return getRemoteHost()
		/// on the wrapped request object.

	virtual void setAttribute(const std::string& name, Object* a);
		/// The default behavior of this method is to return setAttribute(string& name, Attribute a)
		/// on the wrapped request object.
    
	virtual void removeAttribute(const std::string& name);
		/// The default behavior of this method is to call removeAttribute(String name)
		/// on the wrapped request object.
    
	virtual std::locale getLocale() const;
		/// The default behavior of this method is to return getLocale()
 		/// on the wrapped request object.
    
	virtual const std::vector<std::locale>& getLocales() const;
		/// The default behavior of this method is to return getLocales()
 		/// on the wrapped request object.
   
	virtual bool isSecure() const;
		/// The default behavior of this method is to return isSecure()
 		/// on the wrapped request object.

	virtual RequestDispatcher& getRequestDispatcher(const std::string& path);
		/// The default behavior of this method is to return getRequestDispatcher(String path)
 		/// on the wrapped request object.
    
	virtual std::string getRealPath(const std::string& path) const;
		/// The default behavior of this method is to return getRealPath(string& path)
 		/// on the wrapped request object.
    
	virtual int getRemotePort() const;
		/// The default behavior of this method is to return
 		/// getRemotePort() on the wrapped request object.

	virtual std::string getLocalName() const;
		/// The default behavior of this method is to return
 		/// getLocalName() on the wrapped request object.

	virtual std::string getLocalAddr() const;
		/// The default behavior of this method is to return
 		/// getLocalAddr() on the wrapped request object.

	virtual int getLocalPort() const;
		/// The default behavior of this method is to return
 		/// getLocalPort() on the wrapped request object.

private:
	ServletRequest& _request;
};


} } // namespace Poco::Servlet


#endif//Servlet_ServletRequestWrapper_INCLUDED
