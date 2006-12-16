/// Portlet.h

/// Copyright 2003 IBM Corporation and Sun Microsystems, Inc.


#ifndef Portlet_Portlet_INCLUDED
#define Portlet_Portlet_INCLUDED


#ifndef Portlet_PortletBase_INCLUDED
#include "Portlet/PortletBase.h"
#endif
#ifndef Portlet_PortletConfig_INCLUDED
#include "Portlet/PortletConfig.h"
#endif
#ifndef Portlet_ActionRequest_INCLUDED
#include "Portlet/ActionRequest.h"
#endif
#ifndef Portlet_ActionResponse_INCLUDED
#include "Portlet/ActionResponse.h"
#endif
#ifndef Portlet_RenderRequest_INCLUDED
#include "Portlet/RenderRequest.h"
#endif
#ifndef Portlet_RenderResponse_INCLUDED
#include "Portlet/RenderResponse.h"
#endif


Portlet_BEGIN


class CPP_PORTLET_DLL_API PPortlet
	/// The PPortlet interface is used by the portlet container to
	/// invoke the portlets. Every portlet has to implement this interface,
	/// either by directly implementing it, or by using an existing class 
	/// implementing the Portlet interface.
	/// 
	/// A portlet is a Java technology-based web component. It is managed by the portlet container and
	/// processes requests and generates dynamic content as response. Portlets are used by portals as
	/// pluggable user interface components.
	/// 
	/// The content generated by a portlet is called a fragment. A fragment is a piece of
	/// markup (e.g. HTML, XHTML, WML) adhering to certain rules and can be aggregated
	/// with other fragments into a complete document. The content of a portlet is normally
	/// aggregated with the content of other portlets into the portal page. 
	/// 
	/// The portlet container instanciates portlets, manages their lifecycle 
	/// and invoking them to process requests. The lifecycle consists of:
	/// 	
	/// 		initializing the portlet using using the init method
	/// 		request processsing
	/// 		taking the portlet out of service using the destroy method
	/// 
	/// 
	/// Request processing is divided into two types:
	/// 	
	///		action requests handled through the processAction method, 
	///		to perform actions targeted to the portlet
	///		
	///		render requests handled through the render method, 
	///		to perform the render operation
{
public:
	virtual void init(const PortletConfig& config) = 0;
  		/// Called by the portlet container to indicate to a portlet that the 
  		/// portlet is being placed into service.
  		///
  		/// The portlet container calls the init
  		/// method exactly once after instantiating the portlet.
  		/// The init method must complete successfully
  		/// before the portlet can receive any requests.
  		///
  		/// The portlet container cannot place the portlet into service
  		/// if the init method
  		/// 
  		/// 		Throws a PortletException
  		/// 		Does not return within a time period defined by the portlet container.
  		/// 
  		///
  		///
  		/// Parameter config			a PortletConfig object 
  		///					containing the portlet's
  		/// 					configuration and initialization parameters
  		///
  		/// Throws PortletException if an exception has occurred that
  		///	interferes with the portlet's normal operation.
  		/// Throws UnavailableException if the portlet cannot perform the 
		/// initialization at this time.

	virtual void processAction (const ActionRequest& request, ActionResponse& response) = 0;
  		/// Called by the portlet container to allow the portlet to process
  		/// an action request. This method is called if the client request was
  		/// originated by a URL created (by the portlet) with the 
  		/// RenderResponse.createActionURL() method.
  		/// 
  		/// Typically, in response to an action request, a portlet updates state 
  		/// based on the information sent in the action request parameters.
  		/// In an action the portlet may:
  		/// 	
  		/// 		issue a redirect
  		/// 		change its window state
  		/// 		change its portlet mode
  		/// 		modify its persistent state
  		/// 		set render parameters
  		///
  		/// A client request triggered by an action URL translates into one 
  		/// action request and many render requests, one per portlet in the portal page.
  		/// The action processing must be finished before the render requests
  		/// can be issued.
  		///
  		/// Parameter request is the action request.
  		/// Parameter response is the action response.
  		/// Throws PortletException if the portlet has problems fulfilling the request.
  		/// Throws UnavailableException if the portlet is unavailable to process the action 
		/// at this time.
  		/// Throws PortletSecurityException if the portlet cannot fullfill this request 
		/// because of security reasons.
  		/// Throws IOException if the streaming causes an I/O problem.

	virtual void render (const RenderRequest& request, RenderResponse& response) = 0;
  		/// Called by the portlet container to allow the portlet to generate
  		/// the content of the response based on its current state.
  		///
  		/// Parameter   request is the render request
  		/// Parameter   response is the render response
  		///
  		/// Throws PortletException if the portlet has problems fulfilling the
  		/// rendering request.
  		/// Throws UnavailableException if the portlet is unavailable to perform render 
		/// at this time.
  		/// Throws PortletSecurityException if the portlet cannot fullfill this request 
		/// because of security reasons.
  		/// Throws IOException if the streaming causes an I/O problem.
  
	virtual void destroy() = 0;
  		/// Called by the portlet container to indicate to a portlet that the
  		/// portlet is being taken out of service.  
  		/// 
  		/// Before the portlet container calls the destroy method, it should 
  		/// allow any threads that are currently processing requests within 
  		/// the portlet object to complete execution. To avoid
  		/// waiting forever, the portlet container can optionally wait for 
  		/// a predefined time before destroying the portlet object.
  		///
  		/// This method enables the portlet to do the following:
  		/// 	
  		/// 		clean up any resources that it holds (for example, memory,
  		/// file handles, threads) 
		///
  		/// 		make sure that any persistent state is
  		/// synchronized with the portlet current state in memory.
};


Portlet_END


#endif //Portlet_Portlet_INCLUDED
