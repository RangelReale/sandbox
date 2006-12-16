//
// ConfigImpl.cpp
//
// Library: Container
// Package: ContainerCore
// Module:  ConfigImpl
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


#include "Poco/Servlet/Container/ConfigImpl.h"


namespace Poco {
namespace Servlet {
namespace Container {


ConfigImpl::ConfigImpl(const ServletContextImpl& context):
_servletContext(context)
{
}


ConfigImpl::~ConfigImpl()
{
}


const std::string& ConfigImpl::getInitParameter(const std::string& name, 
	const std::string& defValue) const
{
	ParameterMap::const_iterator it = _parameters.find(name);
	if(it != _parameters.end()) return it ->second;

	return defValue;
}


const std::string& ConfigImpl::getInitParameter(const std::string& name) const
{
	return getInitParameter(name, "");
}


std::vector<std::string> ConfigImpl::getInitParameterNames() const
{
	std::vector<std::string> names;

	ParameterMap::const_iterator it = _parameters.begin();
	for(; it != _parameters.end(); ++it)
		names.push_back(it->first);

	return names;
}


void ConfigImpl::setInitParameter(const std::string& name, const std::string& value)
{
	_parameters[name] = value;
}


const ServletContext& ConfigImpl::getContext() const
{ 
	return (_servletContext); 
}


void ConfigImpl::setName(const std::string& name)
{
	_name = name;
}


void ConfigImpl::setDisplayName(const std::string& name)
{
	_displayName = name;
}


void ConfigImpl::setClass(const std::string& name)
{
	_className = name;
}


void ConfigImpl::setLibrary(const std::string& name)
{
	_libraryName = name;
}


const std::string& ConfigImpl::getName() const
{ 
	return _name; 
}


const std::string& ConfigImpl::getDisplayName() const
{
	return _displayName;
}


const std::string& ConfigImpl::getClass() const
{
	return _className;
}


const std::string& ConfigImpl::getLibrary() const
{
	return _libraryName;
}


} } } // namespace Poco::Servlet::Container'
