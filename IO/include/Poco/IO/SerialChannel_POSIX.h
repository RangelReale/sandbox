//
// SerialChannel_POSIX.h
//
// $Id: //poco/Main/Data/include/Poco/IO/SerialChannel_POSIX.h#1 $
//
// Library: IO
// Package: Serial
// Module:  SerialChannel
//
// Definition of the SerialChannelImpl class for POSIX.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef IO_SerialChannel_POSIX_INCLUDED
#define IO_SerialChannel_POSIX_INCLUDED


#include "Poco/IO/IO.h"
#include "Poco/IO/SerialConfig_POSIX.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace IO {


class IO_API SerialChannelImpl
{
protected:
	typedef AutoPtr<SerialConfigImpl> ConfigPtr;

	SerialChannelImpl(SerialConfigImpl* pConfig);
	virtual ~SerialChannelImpl();
	void initImpl();
	void openImpl();
	void closeImpl();
	int readImpl(char* pBuffer, int length);
	int readImpl(char*& pBuffer);
	int writeImpl(const char* buffer, int length);
	const std::string& getNameImpl() const;
	void handleError(const std::string& path);
	static std::string& getErrorText(std::string& buf);

private:
	SerialChannelImpl();
	SerialChannelImpl(const SerialChannelImpl&);
	const SerialChannelImpl& operator = (const SerialChannelImpl&);

	int         _handle;
	ConfigPtr   _pConfig;
	std::string _leftOver;
};


} } // namespace Poco::IO


#endif // IO_SerialChannel_POSIX_INCLUDED
