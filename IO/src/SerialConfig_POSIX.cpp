//
// SerialConfig_POSIX.cpp
//
// $Id: //poco/Main/IO/src/SerialConfig_POSIX.cpp#1 $
//
// Library: IO
// Package: Serial
// Module:  SerialConfig
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


#include "Poco/IO/SerialConfig_POSIX.h"
#include "Poco/Exception.h"
#include <sstream>


using Poco::InvalidArgumentException;


namespace Poco {
namespace IO {


SerialConfigImpl::SerialConfigImpl(SerialConfigImpl::BPSRateImpl bpsRate,
	DataBitsImpl dataBits,
	char parity,
	StartBitsImpl startBits,
	StopBitsImpl stopBits,
	FlowControlImpl flowControl,
	unsigned char xOnChar,
	unsigned char xOffChar,
	bool useEOF,
	unsigned char eofChar,
	int bufferSize,
	int timeout):  
	_useEOF(useEOF)
{
	memset(&_termios, 0, sizeof(_termios)) ;

	setBPSRateImpl(bpsRate);
	setDataBitsImpl(dataBits);
	setStopBitsImpl(stopBits);
	setParityCharImpl(parity);
	setFlowControlImpl(flowControl, xOnChar, xOffChar);
	setBufferSizeImpl(bufferSize);
	setTimeoutImpl(timeout);
}


void SerialConfigImpl::setBPSRateImpl(SerialConfigImpl::BPSRateImpl bpsRate)
{
	if (0 != cfsetospeed(&_termios, bpsRate) ||
		0 != cfsetispeed(&_termios, bpsRate))
		throw SystemException("Can not set baud rate");
}


void SerialConfigImpl::setDataBitsImpl(SerialConfigImpl::DataBitsImpl dataBits)
{
	_termios.c_cflag &= ~(CSIZE);
	_termios.c_cflag |= dataBits;
}


SerialConfigImpl::DataBitsImpl SerialConfigImpl::getDataBitsImpl() const
{
	if (_termios.c_cflag & DATA_BITS_EIGHT_IMPL)
		return DATA_BITS_EIGHT_IMPL;
	else if (_termios.c_cflag & DATA_BITS_SEVEN_IMPL)
		return DATA_BITS_SEVEN_IMPL;
	else if (_termios.c_cflag & DATA_BITS_SIX_IMPL)
		return DATA_BITS_SIX_IMPL;
	else if (_termios.c_cflag & DATA_BITS_FIVE_IMPL)
		return DATA_BITS_FIVE_IMPL;

	throw InvalidAccessException("Number of data bits not set");
}


void SerialConfigImpl::setFlowControlImpl(SerialConfigImpl::FlowControlImpl flowControl,
		unsigned char xOnChar,
		unsigned char xOffChar)
{
	if (FLOW_CTRL_HARDWARE_IMPL == flowControl)
	{
		_termios.c_cflag |= CRTSCTS;
		_termios.c_cflag &= ~(IXON | IXOFF);
	}
	else if (FLOW_CTRL_SOFTWARE_IMPL == flowControl)
	{
		_termios.c_cflag |= (IXON | IXOFF); 
		_termios.c_cflag &= ~CRTSCTS;
	}
	else
		throw InvalidArgumentException("Invalid argument supplied. Flow control not set.");

	_flowControl = flowControl;
}





char SerialConfigImpl::getParityCharImpl() const
{
	if (_termios.c_iflag & ~(INPCK))
		return 'N';
	else
	{
		if (_termios.c_cflag & (PARODD & PARENB))
			return 'O';
		else if (_termios.c_cflag & (~(PARODD) & PARENB))
			return 'E';
	}

	throw InvalidAccessException("Parity not set");
}


void SerialConfigImpl::setParityCharImpl(char parityChar)
{
	switch (parityChar)
	{
	case 'n': case 'N':
		_termios.c_cflag &= ~(PARENB);  // clear parity enable
		_termios.c_iflag &= ~(INPCK);   // disable input parity checking
		return;

	case 'o': case 'O':
		_termios.c_cflag |= (PARODD | PARENB); // enable parity, set to ODD
		_termios.c_iflag |= INPCK;      // enable input parity checking
		return;

	case 'e': case 'E':
		_termios.c_cflag |= PARENB;     // enable parity, default is EVEN
		_termios.c_cflag &= ~(PARODD);  // ensure PARODD is clear
		_termios.c_iflag |= INPCK;      // enable input parity checking
		return;

	default:
		{
			std::ostringstream os;
			os << "SerialConfigImpl::setParityCharImpl(" << parityChar << ')';
			throw InvalidArgumentException(os.str());
		}
	}
}


void SerialConfigImpl::setParityImpl(SerialConfigImpl::ParityImpl parity)
{
	switch (parity)
	{
	case PARITY_NONE_IMPL:
		return setParityCharImpl('N');
	case PARITY_ODD_IMPL:
		return setParityCharImpl('O');
	case PARITY_EVEN_IMPL:
		return setParityCharImpl('E');
	}

	throw InvalidArgumentException("Wrong parity.");
}


SerialConfigImpl::ParityImpl SerialConfigImpl::getParityImpl() const
{
	ParityImpl p;

	switch (getParityCharImpl())
	{
	case 'N':
		p = PARITY_NONE_IMPL;
		break;
	case 'O':
		p = PARITY_ODD_IMPL;
		break;
	case 'E':
		p = PARITY_EVEN_IMPL;
		break;
	}

	return p;
}


void SerialConfigImpl::setStopBitsImpl(SerialConfigImpl::StopBitsImpl stopBits)
{
	if (STOP_TWO_IMPL == stopBits)
		_termios.c_cflag |= CSTOPB;
	else
		_termios.c_cflag &= ~(CSTOPB);
}


SerialConfigImpl::StopBitsImpl SerialConfigImpl::getStopBitsImpl() const
{
	if (_termios.c_cflag & CSTOPB)
		return STOP_TWO_IMPL;
	else
		return STOP_ONE_IMPL;
}


} } // namespace Poco::IO
