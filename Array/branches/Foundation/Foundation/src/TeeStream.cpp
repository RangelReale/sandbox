//
// TeeStream.cpp
//
// $Id: //poco/svn/Foundation/src/TeeStream.cpp#2 $
//
// Library: Foundation
// Package: Streams
// Module:  TeeStream
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


#include "Poco/TeeStream.h"


namespace Poco {


TeeStreamBuf::TeeStreamBuf(): 
	_pIstr(0)
{
}


TeeStreamBuf::TeeStreamBuf(std::istream& istr): 
	_pIstr(&istr)
{
}


TeeStreamBuf::TeeStreamBuf(std::ostream& ostr): 
	_pIstr(0)
{
	_streams.push_back(&ostr);
}


TeeStreamBuf::~TeeStreamBuf()
{
}


void TeeStreamBuf::addStream(std::ostream& ostr)
{
	_streams.push_back(&ostr);
}


int TeeStreamBuf::readFromDevice()
{
	if (_pIstr)
	{
		int c = _pIstr->get();
		if (c != -1) writeToDevice((char) c);
		return c;
	}
	return -1;
}


int TeeStreamBuf::writeToDevice(char c)
{
	for (StreamVec::iterator it = _streams.begin(); it != _streams.end(); ++it)
	{
		(*it)->put(c);
	}
	return charToInt(c);
}


TeeIOS::TeeIOS()
{
	poco_ios_init(&_buf);
}


TeeIOS::TeeIOS(std::istream& istr): _buf(istr)
{
	poco_ios_init(&_buf);
}


TeeIOS::TeeIOS(std::ostream& ostr): _buf(ostr)
{
	poco_ios_init(&_buf);
}


TeeIOS::~TeeIOS()
{
}


void TeeIOS::addStream(std::ostream& ostr)
{
	_buf.addStream(ostr);
}


TeeStreamBuf* TeeIOS::rdbuf()
{
	return &_buf;
}


TeeInputStream::TeeInputStream(std::istream& istr): TeeIOS(istr), std::istream(&_buf)
{
}


TeeInputStream::~TeeInputStream()
{
}


TeeOutputStream::TeeOutputStream(): std::ostream(&_buf)
{
}


TeeOutputStream::TeeOutputStream(std::ostream& ostr): TeeIOS(ostr), std::ostream(&_buf)
{
}


TeeOutputStream::~TeeOutputStream()
{
}


} // namespace Poco
