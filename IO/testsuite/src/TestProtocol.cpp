//
// TestProtocol.cpp
//
// $Id: //poco/1.2/Net/testsuite/src/TestProtocol.cpp#1 $
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


#include "TestProtocol.h"
#include "Poco/IO/Protocol.h"
#include "Poco/IOChannel.h"
#include "Poco/Format.h"
#include "Poco/Exception.h"


using Poco::IO::Protocol;
using Poco::IOChannel;
using Poco::format;
using Poco::InvalidArgumentException;
using Poco::InvalidAccessException;


const std::string TestProtocol::WRITE_BEGIN = "<data%d>";
const std::string TestProtocol::WRITE_END = "</data%d>";


TestProtocol::TestProtocol(IOChannel* pChannel, int number): 
	Protocol(format("TestProtocol%d", number), pChannel), 
	_number(number)
{
}


TestProtocol::TestProtocol(int number): 
	Protocol(format("TestProtocol%d", number)), 
	_number(number)
{
}


TestProtocol::~TestProtocol()
{
}


std::string& TestProtocol::wrap()
{
	std::string& data = buffer();
	std::string buf; 
	format(buf, WRITE_BEGIN, _number);

	buf += data;
	buf.append(format(WRITE_END, _number));
	return data = buf;
}


std::string& TestProtocol::unwrap()
{
	std::string& buf = buffer();
	std::string begin = format(WRITE_BEGIN, _number);
	std::string end = format(WRITE_END, _number);

	std::string::size_type posBegin = buf.find(begin);
	if (std::string::npos == posBegin) throw InvalidArgumentException();
	else posBegin += begin.size();

	std::string::size_type posEnd = buf.find(end);
	if (std::string::npos == posEnd) throw InvalidArgumentException();

	poco_assert (posBegin < posEnd);

	_data.assign(buf.begin() + posBegin, buf.begin() + posEnd);
	return _data;
}

