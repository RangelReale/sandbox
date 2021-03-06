//
// AsyncEvent.h
//
// $Id: //poco/svn/Foundation/include/Poco/AsyncEvent.h#2 $
//
// Library: Foundation
// Package: AsyncIO
// Module:  AsyncEvent
//
// Definition of the AsyncEvent class.
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
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


#ifndef IO_AsyncEvent_INCLUDED
#define IO_AsyncEvent_INCLUDED


#include "Poco/IO/IO.h"


namespace Poco {
namespace IO {


class AsyncCommand;
class AsyncChannel;


class IO_API AsyncEvent
	/// The AsyncEvent class holds information about an event
	/// caused by asynchronous input or output operation.
{
public:
	enum EventKind
	{
		EV_COMMAND_COMPLETED,
		EV_COMMAND_FAILED
	};
	
	AsyncEvent(AsyncCommand* pCommand, AsyncChannel* pChannel, EventKind what);
		/// Creates the AsyncEvent.

	AsyncEvent(const AsyncEvent& event);
		/// Creates a AsyncEvent from another one.

	~AsyncEvent();
		/// Destroys the AsyncEvent.
		
	AsyncEvent& operator = (const AsyncEvent& event);
		/// Assigns a AsyncEvent.
		
	void swap(AsyncEvent& event);
		/// Swaps the event with another one.
		
	AsyncCommand& command() const;
		/// Returns the command that caused the event.
		
	AsyncChannel& channel() const;
		/// Returns the channel that caused the event.
		
	EventKind what() const;
		/// Returns the reason of the event.

private:
	AsyncEvent();
	
	AsyncCommand* _pCommand;
	AsyncChannel* _pChannel;
	EventKind       _what;
};


//
// inlines
//
inline AsyncCommand& AsyncEvent::command() const
{
	return *_pCommand;
}


inline AsyncChannel& AsyncEvent::channel() const
{
	return *_pChannel;
}


inline AsyncEvent::EventKind AsyncEvent::what() const
{
	return _what;
}


} } // namespace Poco::IO


#endif // IO_AsyncEvent_INCLUDED
