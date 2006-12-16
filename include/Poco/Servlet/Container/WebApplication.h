//
// WebApplication.h
//
//
// Library: Container
// Package: ContainerCore
// Module:  WebApplication
//
// Definition of the WebApplication class.
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

#ifndef Container_WebApplication_INCLUDED
#define Container_WebApplication_INCLUDED


#include "Poco/Servlet/Container/ContainerBase.h"
#include "Poco/Servlet/Container/Contained.h"
#include "Poco/Servlet/HttpServlet.h"
#include "Poco/Servlet/HttpSession.h"
#include "Poco/Servlet/Container/ServletContextImpl.h"
#include "Poco/Servlet/Container/ConfigImpl.h"
#include "Poco/Servlet/Container/EntityInfo.h"
#include "Poco/Servlet/Ex/HttpServletDispatcher.h"
#include "Poco/Servlet/Ex/SessionManager.h"
#include "Poco/Servlet/Ex/FilterProvider.h"
#include "Poco/Servlet/Ex/FilterDispatcher.h"
#include "Poco/Logger.h"
#include "Poco/SplitterChannel.h"
#include "Poco/Mutex.h"
#include "Poco/Path.h"
#include "Poco/NotificationCenter.h"
#include "Poco/Util/XMLConfiguration.h"
#include <string>
#include <map>
#include "Poco/Servlet/Ex/ServletProvider.h"


namespace Poco {
namespace Servlet {
namespace Container {


class HttpSessionImpl;
class FilterChainImpl;
class WebApplication;


class HttpSessionListenerImpl : public HttpSessionListener
{
public:
	HttpSessionListenerImpl(WebApplication* pApp);
	void sessionCreated(const HttpSessionEvent& se);
	void sessionDestroyed(const HttpSessionEvent& se);

private:
	HttpSessionListenerImpl();
	WebApplication* _pApp;
};

class HttpServletProviderImpl : public Poco::Servlet::Ex::HttpServletProvider
{
public:
	HttpServletProviderImpl(WebApplication* pApp);
	HttpServlet* getHttpServlet(const std::string& servletName) const;

private:
	HttpServletProviderImpl();
	WebApplication* _pApp;
};

class DefaultFilter : public Filter
{
public:
	void doFilter(ServletRequest& request, ServletResponse& response, const FilterChain* pchain=0) const
	{
		if(pchain) pchain->doFilter(request, response);
	}
};

class FilterProviderImpl : public Poco::Servlet::Ex::FilterProvider
{
public:
	FilterProviderImpl(WebApplication* pApp);
	~FilterProviderImpl();
	const Filter& getFilter(const std::string& filterName) const;
		/// Returns pointer to filter obtained from WebApplication
		/// filter repository.

	const FilterChain& getFilterChain(const Servlet& servlet);
		/// Returns reference to filter chain associated with a servlet.
		/// Returned filter chain shall always have servlet associated 
		/// with it to ensure that the servlet is being called at the end
		/// of chain (even when there are no chained filters) when request 
		/// is routed through FilterDispatcher.

private:
	typedef std::map<std::string, const FilterChainImpl*> FilterChainMap;
	FilterProviderImpl();
	WebApplication*       _pApp;
	FilterChainMap        _chainMap;
	mutable DefaultFilter _filter;
};


typedef RegistrationInfo<ServletConfigImpl> ServletRegInfo;


class HttpServletInfo : public EntityInfo<ServletRegInfo, HttpServlet>
{
public:
	HttpServletInfo(const std::string& name, ServletRegInfo* pRegInfo, HttpServlet* pServlet):
	EntityInfo<ServletRegInfo, HttpServlet>(name, pRegInfo, pServlet)
	{
	}

	const std::string& getSessionId() const
	{
		return _sessionId;
	}

	void setSessionId(const std::string& id)
	{
		_sessionId = id;
	}

private:
	HttpServletInfo();
	HttpServletInfo(const HttpServletInfo&);
	HttpServletInfo& operator=(const HttpServletInfo&);

	std::string _sessionId;
		/// Servlet's session id (if "", no session is associated with servlet)
};


typedef RegistrationInfo<FilterConfigImpl> FilterRegInfo;


class FilterInfo : public EntityInfo<FilterRegInfo, Filter>
{
public:
	FilterInfo(const std::string& name, FilterRegInfo* pRegInfo, Filter* pFilter):
	EntityInfo<FilterRegInfo, Filter>(name, pRegInfo, pFilter)
	{
	}

private:
	FilterInfo();
	FilterInfo(const FilterInfo&);
	FilterInfo& operator=(const FilterInfo&);
};


class Container_API WebApplication : public Contained
{
 public:
	WebApplication(const std::string& base,
		Poco::Servlet::Ex::HttpServletDispatcher& dispatcher,
		Poco::Servlet::Ex::FilterDispatcher* pFilterDispatcher=0);
		/// Constructor.

	~WebApplication();
		/// Destructor.

	typedef std::map<std::string, ServletRegInfo*> ServletRegMap;
		/// Map container type for loaded servlets info (keyed by servlet class name).

	typedef std::map<std::string, FilterRegInfo*> FilterRegMap;
		///  Map container type for loaded filters info (keyed by filter class name).
  
	typedef std::map<std::string, HttpServletInfo*> ServletMap;
		/// Map container type for loaded servlets (keyed by servlet name).

	typedef std::map<std::string, FilterInfo*> FilterMap;
		/// Map container type for loaded filters (keyed by filter name).

	typedef Poco::ClassLoader<HttpServlet> ServletLoader;
	typedef Poco::ClassLoader<Filter> FilterLoader;

	ServletContext& getContext();

	const HttpServlet* createServlet(const std::string& className, const std::string& servletName="");
		/// Creates and initializes a servlet. 

	const HttpServlet* getServlet(const std::string& servletName) const;
		/// Returns pointer to requested servlet. If servlet is not found,
		/// returns 0.

	const Filter* createFilter(const std::string& className, const std::string& filterName="");
		/// Creates and initializes a filter.

	const Filter* getFilter(const std::string& filterName) const;
		/// Returns pointer to requested filter. If servlet is not found,
		/// returns 0.

	bool isServletClassRegistered(const std::string& className);
		/// Returns true if the servlet class name is known to the web application.

	bool isFilterClassRegistered(const std::string& className);
		/// Returns true if the filter class name is known to the web application.

	bool isServletLoaded(const std::string& servletName);
		/// Returns true if the servlet is loaded.

	bool isFilterLoaded(const std::string& servletName);
		/// Returns true if the filter is loaded.

	void setInitParameter(const std::string& name, const std::string& value);
	std::string getInitParameter(const std::string& name) const;
	std::string getInitParameter(const std::string& name, const std::string& defValue) const;
	
	Poco::Servlet::Ex::SessionManager* getSessionManager();

private:

	void init();
		/// Initializes the web application.

	void initServlets();
		/// Fills the ServletRegInfo map with registered servlets information and 
		/// loads servlets marked as pre-load.
		/// (Pre-load means the servlet is created and loaded at container startup 
		///  rather than upon the first request for it.)

	void initFilters();
		
	void setInitParameters();
		/// Read initialization parameters.

	void setupDispatchers();
		/// Assign values dispatchers need to be aware of such as
		/// mapping patterns, session manager etc...

	void createContext();
		/// (Re)creates the context.

	void deleteServlet(HttpServletInfo* psi, const std::string& reason="");
		/// Deletes the servlet entry from servlets map and cleans al the resources.
		/// Exception are singletons and servlets with autoDelete set to true which
		/// are deleted by the class loader.

	void deleteFilter(FilterInfo* psi, const std::string& reason="");
		/// Deletes the filter entry from filters map and cleans al the resources.

	std::string getSessionId(const std::string& name);
		/// Utility method to extract session name from the servlet name.
		/// (servlet names have the "name#session" format)

	std::string getServletBaseName(const std::string& name);
		/// Utility method to extract servlet base name from the servlet name.
		/// (servlet names have the "name#session" format)

	std::vector<std::string>& getServletNames(const std::string& id, std::vector<std::string>& servlets);
		/// Utility method to retrieve servlet names belonging to the session id.

	bool WebApplication::extractEntities(ConfigImpl& SConfig, const std::string& entityName, int position);
		/// Utility method to extract entities configuration from deployment descriptor.
		/// Returns 0 if entity at position is not found.

	bool loadServletSharedLib(const std::string& fileName);
		/// Loads the servlet shared lib.

	bool loadFilterSharedLib(const std::string& fileName);
		/// Loads the filter shared lib.

	ServletContextImpl* _pContext;
		/// Web application context.
	
	Poco::Servlet::Ex::SessionManager* _pSessionManager;
		/// Pointer to the session manager.

	ServletRegMap _regServletMap;
		/// All servlets known to this application.

	FilterRegMap _regFilterMap;
		/// All servlets known to this application.
  
	ServletMap _servletMap;
		/// All loaded servlet instances.

	FilterMap _filterMap;
		/// All loaded filter instances.
	 
	Poco::Servlet::Ex::HttpServletDispatcher& _servletDispatcher;
		/// Dispatcher for servlet requests reference.

	Poco::Servlet::Ex::FilterDispatcher* _pFilterDispatcher;
		/// Pointer to dispatcher for filters.

	static Poco::FastMutex   _mutex;

	HttpSessionListenerImpl _sessionListener;
	HttpServletProviderImpl _servletProvider;
	FilterProviderImpl			_filterProvider;

	ServletLoader _servletLoader;
	FilterLoader _filterLoader;

	MimeMap* _pMimeMap;

	friend class HttpSessionListenerImpl;
	friend class HttpServletProviderImpl;
	friend class FilterProviderImpl;
};


///
/// inlines
///


inline Poco::Servlet::Ex::SessionManager* WebApplication::getSessionManager()
{
	return this->_pSessionManager;
}


} } } // namespace Poco::Servlet::Container


#endif //Container_WebApplication_INCLUDED
