//
// SesssionHandle.cpp
//
// $Id: //poco/1.4/Data/PgSQL/src/SessionHandle.cpp#1 $
//
// Library: Data
// Package: PgSQL
// Module:  SessionHandle
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


#include "Poco/Data/PgSQL/SessionHandle.h"
#include "Poco/Data/DataException.h"

#define POCO_PgSQL_VERSION_NUMBER ((NDB_VERSION_MAJOR<<16) | (NDB_VERSION_MINOR<<8) | (NDB_VERSION_BUILD&0xFF))

namespace Poco {
namespace Data {
namespace PgSQL {


SessionHandle::SessionHandle():
    _pHandle(0)
{
}

SessionHandle::~SessionHandle()
{
	close();
}

/*
void SessionHandle::options(PgSQL_option opt)
{
	if (PgSQL_options(_pHandle, opt, 0) != 0)
		throw ConnectionException("PgSQL_options error", _pHandle);
}


void SessionHandle::options(PgSQL_option opt, bool b)
{
	bool tmp = b;
	if (PgSQL_options(_pHandle, opt, &tmp) != 0)
		throw ConnectionException("PgSQL_options error", _pHandle);
}

void SessionHandle::options(PgSQL_option opt, unsigned int i)
{
#if (POCO_PgSQL_VERSION_NUMBER < 0x050108)
	const char* tmp = (const char *)&i;
#else
	const void* tmp = (const void *)&i;
#endif
	if (PgSQL_options(_pHandle, opt, tmp) != 0)
		throw ConnectionException("PgSQL_options error", _pHandle);
}
*/

void SessionHandle::connect(const std::string& conninfo)
{
    _pHandle = PQconnectdb(conninfo.c_str());
	if (!_pHandle)
		throw ConnectionFailedException("PQconnectdb() error");
}

void SessionHandle::close()
{
	if (_pHandle)
	{
		PQfinish(_pHandle);
		_pHandle = 0;
	}
}

/*
void SessionHandle::startTransaction()
{
    if (PgSQL_autocommit(_pHandle, false) != 0)
		throw TransactionException("Start transaction failed.", _pHandle);
}


void SessionHandle::commit()
{
    if (PgSQL_commit(_pHandle) != 0)
		throw TransactionException("Commit failed.", _pHandle);
}


void SessionHandle::rollback()
{
    if (PgSQL_rollback(_pHandle) != 0)
		throw TransactionException("Rollback failed.", _pHandle);
}
*/

}}} // Poco::Data::PgSQL