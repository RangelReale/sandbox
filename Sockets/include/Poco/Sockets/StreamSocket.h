//
// StreamSocket.h
//
// $Id: //poco/svn/Net/include/Poco/Net/StreamSocket.h#2 $
//
// Library: Net
// Package: Sockets
// Module:  StreamSocket
//
// Definition of the StreamSocket class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
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


#ifndef Sockets_StreamSocket_INCLUDED
#define Sockets_StreamSocket_INCLUDED


#include "Poco/Sockets/Sockets.h"
#include "Poco/Sockets/Socket.h"


namespace Poco {
namespace Sockets {


class StreamSocketImpl;


class Sockets_API StreamSocket: public Socket
	/// This class provides an interface to a
	/// TCP stream socket.
{
public:
	StreamSocket();
		/// Creates an unconnected stream socket.
		///
		/// Before sending or receiving data, the socket
		/// must be connected with a call to connect().

	StreamSocket(const SocketAddress& toAddress, const SocketAddress* pFromAddress = 0);
		/// Creates a stream socket and connects it to
		/// the socket specified by address. The optional (pFromAddress) 
		/// second argument is used only by UNIX domain sockets which must be 
		/// explicitly bound to local address.

	StreamSocket(const Socket& socket);
		/// Creates the StreamSocket with the SocketImpl
		/// from another socket. The SocketImpl must be
		/// a StreamSocketImpl, otherwise an InvalidArgumentException
		/// will be thrown.

	virtual ~StreamSocket();
		/// Destroys the StreamSocket.

	StreamSocket& operator = (const Socket& socket);
		/// Assignment operator.
		///
		/// Releases the socket's SocketImpl and
		/// attaches the SocketImpl from the other socket and
		/// increments the reference count of the SocketImpl.	

	void connect(const SocketAddress& address, const SocketAddress* pFromAddress = 0);
		/// Initializes the socket and establishes a connection to 
		/// the TCP server at the given address. The optional (pFromAddress) 
		/// second argument is used only by UNIX domain sockets which must be 
		/// explicitly bound to local address.

	void connect(const SocketAddress& address,
		const Poco::Timespan& timeout,
		const SocketAddress* pFromAddress = 0);
		/// Initializes the socket, sets the socket timeout and 
		/// establishes a connection to the TCP server at the given address.
		/// The optional (pFromAddress) 
		/// second argument is used only by UNIX domain sockets which must be 
		/// explicitly bound to local address.

	void connectNB(const SocketAddress& address, const SocketAddress* pFromAddress = 0);
		/// Initializes the socket and establishes a connection to 
		/// the TCP server at the given address. Prior to opening the
		/// connection the socket is set to nonblocking mode. The optional (pFromAddress) 
		/// second argument is used only by UNIX domain sockets which must be 
		/// explicitly bound to local address.

	void shutdownReceive();
		/// Shuts down the receiving part of the socket connection.
		
	void shutdownSend();
		/// Shuts down the sending part of the socket connection.
		
	void shutdown();
		/// Shuts down both the receiving and the sending part
		/// of the socket connection.
	
	int sendBytes(const void* buffer, int length, int flags = 0);
		/// Sends the contents of the given buffer through
		/// the socket.
		///
		/// Returns the number of bytes sent, which may be
		/// less than the number of bytes specified.

	int receiveBytes(void* buffer, int length, int flags = 0);
		/// Receives data from the socket and stores it
		/// in buffer. Up to length bytes are received.
		///
		/// Returns the number of bytes received. 
		/// A return value of 0 means a graceful shutdown 
		/// of the connection from the peer.
		///
		/// Throws a TimeoutException if a receive timeout has
		/// been set and nothing is received within that interval.
		/// Throws a NetException (or a subclass) in case of other errors.

	void sendUrgent(unsigned char data);
		/// Sends one byte of urgent data through
		/// the socket.
		///
		/// The data is sent with the MSG_OOB flag.
		///
		/// The preferred way for a socket to receive urgent data
		/// is by enabling the SO_OOBINLINE option.

public:
	StreamSocket(SocketImpl* pImpl);
		/// Creates the Socket and attaches the given SocketImpl.
		/// The socket takes owership of the SocketImpl.
		///
		/// The SocketImpl must be a StreamSocketImpl, otherwise
		/// an InvalidArgumentException will be thrown.

	friend class ServerSocket;
	friend class SocketIOS;
};


} } // namespace Poco::Sockets


#endif // Sockets_StreamSocket_INCLUDED