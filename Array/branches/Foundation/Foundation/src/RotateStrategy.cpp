//
// RotateStrategy.cpp
//
// $Id: //poco/svn/Foundation/src/RotateStrategy.cpp#2 $
//
// Library: Foundation
// Package: Logging
// Module:  FileChannel
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/RotateStrategy.h"


namespace Poco {


//
// RotateStrategy
//


RotateStrategy::RotateStrategy()
{
}


RotateStrategy::~RotateStrategy()
{
}


//
// RotateByIntervalStrategy
//


RotateByIntervalStrategy::RotateByIntervalStrategy(const Timespan& span): _span(span)
{
	if (span.totalMicroseconds() <= 0) throw InvalidArgumentException("time span must be greater than zero");
}


RotateByIntervalStrategy::~RotateByIntervalStrategy()
{
}


bool RotateByIntervalStrategy::mustRotate(LogFile* pFile)
{
	Timestamp now;
	return _span <= now - pFile->creationDate();
}


//
// RotateBySizeStrategy
//


RotateBySizeStrategy::RotateBySizeStrategy(UInt64 size): _size(size)
{
	if (size == 0) throw InvalidArgumentException("size must be greater than zero");
}


RotateBySizeStrategy::~RotateBySizeStrategy()
{
}


bool RotateBySizeStrategy::mustRotate(LogFile* pFile)
{
	return pFile->size() >= _size;
}


} // namespace Poco
