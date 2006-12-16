//
// ServletResponseWrapper.cpp
//
//
// Library: Servlet
// Package: Servlet
// Module:  ServletResponseWrapper
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
// The code in this file is derived from Apache Tomcat project
// Copyright (c) 2004 The Apache Software Foundation.
// http://www.apache.org/licenses/LICENSE-2.0
// 


#include "Poco/Servlet/ServletResponseWrapper.h"


namespace Poco {
namespace Servlet {


ServletResponseWrapper::ServletResponseWrapper(ServletResponse& response):
	_response(response)
{
}


ServletResponseWrapper::~ServletResponseWrapper()
{
}


ServletResponse* ServletResponseWrapper::getResponse() 
{
	return &_response;
}	


void ServletResponseWrapper::setResponse(ServletResponse& response) 
{
  _response = response;
}


void ServletResponseWrapper::setCharacterEncoding(const std::string& charset) 
{
	_response.setCharacterEncoding(charset);
}


const std::string ServletResponseWrapper::getCharacterEncoding() const
{
	return _response.getCharacterEncoding();
}


ServletOutputStream& ServletResponseWrapper::getOutputStream() 
{
	return _response.getOutputStream();
}  


PrintWriter& ServletResponseWrapper::getWriter()
{
	return _response.getWriter();
}


void ServletResponseWrapper::setContentLength(int len) 
{
	_response.setContentLength(len);
}


void ServletResponseWrapper::setContentType(const std::string& type) 
{
	_response.setContentType(type);
}


std::string ServletResponseWrapper::getContentType() 
{
	return _response.getContentType();
}


void ServletResponseWrapper::setBufferSize(int size) 
{
	_response.setBufferSize(size);
}


int ServletResponseWrapper::getBufferSize() 
{
	return _response.getBufferSize();
}


void ServletResponseWrapper::flushBuffer()
{
	_response.flushBuffer();
}


bool ServletResponseWrapper::isCommitted() 
{
	return _response.isCommitted();
}


void ServletResponseWrapper::reset() 
{
	_response.reset();
}


void ServletResponseWrapper::resetBuffer() 
{
	_response.resetBuffer();
}


void ServletResponseWrapper::setLocale(const std::locale& loc) 
{
	_response.setLocale(loc);
}


std::locale ServletResponseWrapper::getLocale() 
{
	return _response.getLocale();
}


} } // namespace Poco::Servlet
