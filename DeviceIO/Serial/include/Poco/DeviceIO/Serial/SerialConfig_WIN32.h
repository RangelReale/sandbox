//
// SerialConfig_WIN32.h
//
// $Id: //poco/Main/DeviceIO/include/Poco/DeviceIO/Serial/SerialConfig_WIN32.h#1 $
//
// Library: Serial
// Package: Serial
// Module:  SerialConfig
//
// Definition of the SerialConfigImpl class for WIN32.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
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


#ifndef Serial_SerialConfig_WIN32_INCLUDED
#define Serial_SerialConfig_WIN32_INCLUDED


#include "Poco/DeviceIO/DeviceIO.h"
#include <windows.h>


namespace Poco {
namespace DeviceIO {
namespace Serial {


class Serial_API SerialConfigImpl: public RefCountedObject
{
public:
	static const int MSEC = 1000;
	static const int NOT_SUPPORTED = -1;

	enum DataBitsImpl
	{
		DATA_BITS_FIVE_IMPL = 5,
		DATA_BITS_SIX_IMPL = 6,
		DATA_BITS_SEVEN_IMPL = 7,
		DATA_BITS_EIGHT_IMPL = 8
	};

	enum ParityImpl
	{
		PARITY_NONE_IMPL = NOPARITY,
		PARITY_ODD_IMPL = ODDPARITY,
		PARITY_EVEN_IMPL = EVENPARITY,
		PARITY_MARK_IMPL = MARKPARITY,
		PARITY_SPACE_IMPL = SPACEPARITY
	};

	enum StartBitsImpl
	{
		START_ONE_IMPL = ONESTOPBIT,
		START_ONE5_IMPL = ONE5STOPBITS,
		START_TWO_IMPL = TWOSTOPBITS
	};

	enum StopBitsImpl
	{
		STOP_ONE_IMPL = ONESTOPBIT,
		STOP_ONE5_IMPL = ONE5STOPBITS,
		STOP_TWO_IMPL = TWOSTOPBITS
	};

	enum FlowControlImpl
	{
		FLOW_CTRL_HARDWARE_IMPL,
		FLOW_CTRL_SOFTWARE_IMPL
	};

	enum BPSRateImpl
	{
		BPS_NS_IMPL = -1,//not supported
		BPS_110_IMPL = CBR_110,
		BPS_300_IMPL = CBR_300,
		BPS_600_IMPL = CBR_600,
		BPS_1200_IMPL = CBR_1200,
		BPS_2400_IMPL = CBR_2400,
		BPS_4800_IMPL = CBR_4800,
		BPS_9600_IMPL = CBR_9600,
		BPS_14400_IMPL = CBR_14400,
		BPS_19200_IMPL = CBR_19200,
		BPS_38400_IMPL = CBR_38400,
		BPS_57600_IMPL = CBR_57600,
		BPS_115200_IMPL = CBR_115200,
		BPS_128000_IMPL = CBR_128000,
		BPS_230400_IMPL  = BPS_NS_IMPL,
		BPS_256000_IMPL = CBR_256000,
		BPS_460800_IMPL  = BPS_NS_IMPL
	};

	virtual const std::string& name() const = 0;

protected:
	SerialConfigImpl(BPSRateImpl bpsRate,
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
		int timeout);

	virtual ~SerialConfigImpl();

	void setBPSRateImpl(BPSRateImpl bpsRate);
	void setDataBitsImpl(DataBitsImpl dataBits);
	void setParityImpl(ParityImpl parity);
	void setParityCharImpl(char parityChar);
	void setStartBitsImpl(StartBitsImpl startBits);
	void setStopBitsImpl(StopBitsImpl stopBits);
	void setFlowControlImpl(FlowControlImpl flowControl,
		unsigned char xOnChar,
		unsigned char xOffChar);
	void setUseXonXoffImpl(unsigned char xOnChar,
		unsigned char xOffChar);
	void setXonCharImpl(unsigned char xOn);
	void setXoffCharImpl(unsigned char xOff);
	void setUseEOFImpl(bool useEOF);
	void setEOFCharImpl(unsigned char eof);
	void setBufferSizeImpl(int size);
	void setTimeoutImpl(int timeout);
	void setBlockingImpl();

	BPSRateImpl getBPSRateImpl() const;
	DataBitsImpl getDataBitsImpl() const;
	ParityImpl getParityImpl() const;
	char getParityCharImpl() const;
	StartBitsImpl getStartBitsImpl() const;
	StopBitsImpl getStopBitsImpl() const;
	FlowControlImpl getFlowControlImpl() const;
	bool getUseXonXoffImpl() const;
	unsigned char getXonCharImpl() const;
	unsigned char getXoffCharImpl() const;
	bool getUseEOFImpl() const;
	unsigned char getEOFCharImpl() const;
	int getBufferSizeImpl() const;
	int getTimeoutImpl() const;

	DCB& dcb();
	COMMTIMEOUTS& commTimeouts();

private:
	SerialConfigImpl();

	DCB             _dcb;
	COMMTIMEOUTS    _cto;
	FlowControlImpl _flowControl;
	bool            _useEOF;
	int             _bufferSize;

	friend class SerialChannelImpl;
};


//
// inlines
//
inline void SerialConfigImpl::setBPSRateImpl(SerialConfigImpl::BPSRateImpl bpsRate)
{
	_dcb.BaudRate = bpsRate;
}


inline void SerialConfigImpl::setDataBitsImpl(DataBitsImpl dataBits)
{
	_dcb.ByteSize = dataBits;
}


inline void SerialConfigImpl::setParityImpl(SerialConfigImpl::ParityImpl parity)
{
	_dcb.fParity = (parity != PARITY_NONE_IMPL);
	_dcb.Parity = parity;
}


inline void SerialConfigImpl::setStartBitsImpl(SerialConfigImpl::StartBitsImpl startBits)
{
	_dcb.StopBits = startBits;
}


inline void SerialConfigImpl::setStopBitsImpl(SerialConfigImpl::StopBitsImpl stopBits)
{
	_dcb.StopBits = stopBits;
}


inline void SerialConfigImpl::setUseEOFImpl(bool useEOF)
{
	_useEOF = useEOF;
}


inline void SerialConfigImpl::setEOFCharImpl(unsigned char eof)
{
	_dcb.EofChar = eof;
}


inline void SerialConfigImpl::setBufferSizeImpl(int size)
{
	_bufferSize = size;
}


inline void SerialConfigImpl::setBlockingImpl()
{
	ZeroMemory(&_cto, sizeof(COMMTIMEOUTS));
}


inline SerialConfigImpl::BPSRateImpl SerialConfigImpl::getBPSRateImpl() const
{
	return (SerialConfigImpl::BPSRateImpl) _dcb.BaudRate;
}


inline SerialConfigImpl::DataBitsImpl SerialConfigImpl::getDataBitsImpl() const
{
	return (DataBitsImpl) _dcb.ByteSize;
}


inline SerialConfigImpl::ParityImpl SerialConfigImpl::getParityImpl() const
{
	return (SerialConfigImpl::ParityImpl) _dcb.Parity;
}


inline SerialConfigImpl::StartBitsImpl SerialConfigImpl::getStartBitsImpl() const
{
	return (SerialConfigImpl::StartBitsImpl) _dcb.StopBits;
}


inline SerialConfigImpl::StopBitsImpl SerialConfigImpl::getStopBitsImpl() const
{
	return (SerialConfigImpl::StopBitsImpl) _dcb.StopBits;
}


inline SerialConfigImpl::FlowControlImpl SerialConfigImpl::getFlowControlImpl() const
{
	return _flowControl;
}


inline bool SerialConfigImpl::getUseXonXoffImpl() const
{
	return (_dcb.XonChar != _dcb.XoffChar);
}


inline unsigned char SerialConfigImpl::getXonCharImpl() const
{
	return _dcb.XonChar;
}


inline unsigned char SerialConfigImpl::getXoffCharImpl() const
{
	return _dcb.XoffChar;
}


inline bool SerialConfigImpl::getUseEOFImpl() const
{
	return _useEOF;
}


inline unsigned char SerialConfigImpl::getEOFCharImpl() const
{
	return _dcb.EofChar;
}


inline int SerialConfigImpl::getBufferSizeImpl() const
{
	return _bufferSize;
}



inline int SerialConfigImpl::getTimeoutImpl() const
{
	return _cto.ReadTotalTimeoutConstant;
}


inline DCB& SerialConfigImpl::dcb()
{
	return _dcb;
}


inline COMMTIMEOUTS& SerialConfigImpl::commTimeouts()
{
	return _cto;
}


} } } // namespace Poco::DeviceIO::Serial


#endif // Serial_SerialConfig_WIN32_INCLUDED
