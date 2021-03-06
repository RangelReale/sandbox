//
// DNSTest.cpp
//
// $Id: //poco/svn/Net/testsuite/src/DNSTest.cpp#2 $
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


#include "DNSTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Sockets/DNS.h"
#include "Poco/Sockets/HostEntry.h"
#include "Poco/Sockets/SocketException.h"


using Poco::Sockets::DNS;
using Poco::Sockets::Address;
using Poco::Sockets::HostEntry;
using Poco::Sockets::InvalidAddressException;
using Poco::Sockets::HostNotFoundException;
using Poco::Sockets::ServiceNotFoundException;
using Poco::Sockets::NoAddressFoundException;


DNSTest::DNSTest(const std::string& name): CppUnit::TestCase(name)
{
}


DNSTest::~DNSTest()
{
}


void DNSTest::testHostByName()
{
	HostEntry he1 = DNS::hostByName("www.appinf.com");
	assert (he1.name() == "appinf.com");
	assert (!he1.aliases().empty());
	assert (he1.aliases()[0] == "www.appinf.com");
	assert (he1.addresses().size() == 1);
	assert (he1.addresses()[0].toString() == "216.146.46.35");
	
	try
	{
		HostEntry he1 = DNS::hostByName("nohost.appinf.com");
		fail("host not found - must throw");
	}
	catch (HostNotFoundException&)
	{
	}
	catch (NoAddressFoundException&)
	{
	}
}


void DNSTest::testHostByAddress()
{
	Address ip1("213.229.60.82");
	HostEntry he1 = DNS::hostByAddress(ip1);
	assert (he1.name() == "quentin.inode.at");
	assert (he1.aliases().empty());
	assert (he1.addresses().size() == 1);
	assert (he1.addresses()[0].toString() == "213.229.60.82");
	
	Address ip2("10.0.244.253");
	try
	{
		HostEntry he2 = DNS::hostByAddress(ip2);
		fail("host not found - must throw");
	}
	catch (HostNotFoundException&)
	{
	}
	catch (NoAddressFoundException&)
	{
	}
}


void DNSTest::testResolve()
{
}


void DNSTest::setUp()
{
}


void DNSTest::tearDown()
{
}


CppUnit::Test* DNSTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("DNSTest");

	CppUnit_addTest(pSuite, DNSTest, testHostByName);
	CppUnit_addTest(pSuite, DNSTest, testHostByAddress);
	CppUnit_addTest(pSuite, DNSTest, testResolve);

	return pSuite;
}
