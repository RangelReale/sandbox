//
// HttpSessionImpl.cpp
//
// Library: Container
// Package: ContainerCore
// Module:  HttpSessionImpl
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


#include "Poco/Servlet/Container/HttpSessionImpl.h"
#include "Poco/Servlet/Servlet.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Timer.h"
#include "Poco/ThreadPool.h"
#include "Poco/Exception.h"


namespace Poco {
namespace Servlet {
namespace Container {


Poco::UInt64 HttpSessionImpl::_seq = 0;


HttpSessionImpl::HttpSessionImpl(): 
	_startTime(time(0)), 
	_lastAccessTime(0), 
	_new(true), 
	_valid(true), 
	_maxInactiveInterval(INDEFINITE), 
	_pTimer(0), 
	_pCallback(0),
	_pSessionListener(0),
	_pThreadPool(0)
{
	_id = NumberFormatter::format(++_seq);
	setValue(_id);
}


HttpSessionImpl::HttpSessionImpl(long maxInactiveInterval, HttpSessionListener* pSessionListener): 
	_startTime(time(0)), 
	_lastAccessTime(0), 
	_new(true), 
	_valid(true),
	_maxInactiveInterval(maxInactiveInterval), 
	_pTimer(0), 
	_pCallback(0),
	_pSessionListener(pSessionListener),
	_pThreadPool(0)
{
	_id = NumberFormatter::format(++_seq);
	setValue(_id);

	if(_pSessionListener) 
		_pSessionListener->sessionCreated(HttpSessionEvent(this));

	startTimer();
}


HttpSessionImpl::~HttpSessionImpl()
{
	if(_pSessionListener) 
		_pSessionListener->sessionDestroyed(HttpSessionEvent(this));

	if(_pTimer) _pTimer->stop();
	delete _pTimer;
	delete _pCallback;
	delete _pThreadPool;
}


time_t HttpSessionImpl::getCreationTime() const
{
	return _startTime;
}


std::string HttpSessionImpl::getId() const
{
	return _id;
}


time_t HttpSessionImpl::getLastAccessedTime() const
{
	return _lastAccessTime;
}


void HttpSessionImpl::setLastAccessedTimeNS(time_t t)
{
	if(!isValidNS()) return;

	if(0 == t) t = time(0);
	_new = false;
	_lastAccessTime = t;
	restartTimer();
}


const ServletContext& HttpSessionImpl::getServletContext() const
{
	if(_pContext) return *_pContext;

	throw NullPointerException("HttpSessionImpl::_pContext");
}


void HttpSessionImpl::setServletContext(ServletContext* pContext)
{
	if(!isValidNS()) return;
	_pContext = pContext;
}


void HttpSessionImpl::setMaxInactiveInterval(time_t interval)
{
	if(!isValidNS()) return;
	_maxInactiveInterval = interval;
	restartTimer();
}


long HttpSessionImpl::getMaxInactiveInterval() const
{
	return _maxInactiveInterval;
}


const Object* HttpSessionImpl::getAttribute(const std::string& name) const
{
	ObjectMap::const_iterator it = _attributes.find(name);

	if(_attributes.end() != it)	return it->second;

	return 0;
}


const Object* HttpSessionImpl::getValue(const std::string& name) const
{
	return getAttribute(name);
}


const std::vector<std::string>& HttpSessionImpl::getAttributeNames() const
{
	_attributeNames.clear();
	ObjectMap::const_iterator it = _attributes.begin();
	for(; it != _attributes.end(); ++it) _attributeNames.push_back(it->first);

	return _attributeNames;
}


const std::vector<std::string>& HttpSessionImpl::getValueNames() const
{
	return getAttributeNames();
}


void HttpSessionImpl::setAttribute(const std::string& name, Object& value)
{
	if(!isValidNS()) return;
	_attributes[name] = &value;
}


void HttpSessionImpl::removeAttribute(const std::string& name)
{
	if(!isValidNS()) return;
	ObjectMap::iterator it = _attributes.find(name);

	if(_attributes.end() != it)	_attributes.erase(it);
}


void HttpSessionImpl::removeValue(const std::string& name)
{
	if(!isValidNS()) return;
	removeAttribute(name);
}


void HttpSessionImpl::invalidate()
{
	_valid = false;
}


bool HttpSessionImpl::isValidNS() const
{
	return _valid;
}


bool HttpSessionImpl::isNew() const
{
	return _new;
}


void HttpSessionImpl::onTimer(Timer& timer)
{
	invalidate();
}


void HttpSessionImpl::startTimer()
{
	if(!isValidNS()) return;
	delete _pTimer; _pTimer = 0;
	delete _pThreadPool; _pThreadPool = 0;
	if(expires())
	{
		_pTimer = new Timer(_maxInactiveInterval*1000, _maxInactiveInterval*1000);
		_pCallback = new TimerCallback<HttpSessionImpl>(*this, &HttpSessionImpl::onTimer);
		_pThreadPool = new ThreadPool(2, 100);
		_pTimer->start(*_pCallback, *_pThreadPool);
	}
}


void HttpSessionImpl::restartTimer()
{
	if(!isValidNS()) return;
	if(!_pTimer) 
	{
		startTimer();
	}
	else
	{
		if(expires())
		{
			_pTimer->stop();
			_pTimer->setStartInterval(_maxInactiveInterval*1000);
			_pTimer->start(*_pCallback);
		}
	}
}


} } } // namespace Poco::Servlet::Container'
