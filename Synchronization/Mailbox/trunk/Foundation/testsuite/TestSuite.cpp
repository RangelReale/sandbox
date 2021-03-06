//
// CyclicBarrier.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/CyclicBarrier.cpp#5 $
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


#include "Poco/Thread.h"
#include "Poco/Mailbox.h"
#include "Poco/Random.h"
#include <assert.h>

#include <iostream>
#if defined(__sun) && defined(__SVR4)
#define __EXTENSIONS__
#include <limits.h>
#endif


using Poco::Thread;
using Poco::Runnable;
using Poco::Event;
using Poco::Mailbox;

typedef int TMessage;

typedef Poco::Mailbox<TMessage, Poco::Mutex> IntMailbox;

static IntMailbox gMailbox(10);
static int gCount = 0;

class Sender: public Runnable
{
public:
	Sender() 
	{

	}

	void run()
	{
		try
		{
			while(gCount++ < 100){
				TMessage msg = rg.next(100);
				std::cout << "sender: " << msg << std::endl;
				gMailbox.post(msg);
				Thread::sleep(rg.next(10));
			}
		}
		catch(...)
		{
			std::cout << "error\n";
		}
		

	}

private:
	Poco::Random rg;
};

class Receiver: public Runnable
{
public:
	Receiver()
	{
	}

	void run()
	{
		try
		{
			while(gCount<100){
				TMessage msg = gMailbox.pend();
				std::cout << "receiver: " << msg << std::endl;
			}
		}
		catch(Poco::TimeoutException& except)
		{
			std::cout << except.displayText() << std::endl;
			return;
		}
		catch(Poco::NoPermissionException& except)
		{
			std::cout << except.displayText() << std::endl;
			return;
		}
		catch(...)
		{
			std::cout << "unexpected exception!\n";
			return;
		}
	}
};

void testQuery()
{
	assert(gMailbox.length() == 10);
	TMessage msg = 1;
	assert(gMailbox.empty());
	gMailbox.post(msg);
	assert(gMailbox.size() == 1);
	assert(!gMailbox.empty());
	msg = gMailbox.pend();
	assert(gMailbox.size() == 0);
	assert(gMailbox.empty());
}

void testPost()
{
	TMessage msg = 1;
	IntMailbox mailbox(1);
	mailbox.post(msg);
	bool ret = mailbox.tryPost(msg, 1000);
	assert(!ret);
	mailbox.pend();
	ret = mailbox.tryPost(msg, 1000);
	assert(ret);
}

void testPend()
{
	TMessage msg1 = 1;
	IntMailbox mailbox(2);
	mailbox.post(msg1);
	mailbox.post(msg1);
	assert(mailbox.size() == 2);
	TMessage msg2 = mailbox.pend();
	assert(msg2 == msg1);
	msg2 = mailbox.pend();
	assert(msg2 == msg1);

	try
	{
		TMessage msg3 = mailbox.tryPend(1000);
	}
	catch(Poco::TimeoutException & except)
	{       
		std::cout << except.displayText() << std::endl;
	}
	catch(...)
	{
		assert("unexpected exception!\n");
	}

	TMessage msg4;
	bool ret = mailbox.tryPend(msg4, 1000);
	assert(!ret);
}

void testBlockPostPend()
{
    gCount = 0;
	Thread thread1;
	Thread thread2;
	Sender sender;    
	Receiver receiver;    

	thread1.start(sender);
	thread2.start(receiver);

	thread1.join();
	thread2.join();
}

void testReset()
{
	Thread thread1("thread1");
	Thread thread2("thread2");
	Thread thread3("thread3");
	Thread thread4("thread4");

	Receiver receiver;    

	bool isReset = gMailbox.isReset();
	assert(!isReset);

	thread1.start(receiver);
	thread2.start(receiver);
	thread3.start(receiver);
	thread4.start(receiver);

	try
	{
		gMailbox.reset();
	}
	catch(...)
	{
		assert(0);
	}

	isReset = gMailbox.isReset();
	assert(isReset);
	
	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

	try
	{
		TMessage msg = 1;
		gMailbox.post(msg);
	}
	catch(Poco::NoPermissionException& except)
	{
		std::cout << except.displayText() << std::endl;
        return;
	}
	catch(...)
	{
		std::cout << "unexpected exception!\n";
        return;
	}

}

int main()
{
	testQuery();
	testPost();
	testPend();
	testBlockPostPend();
	testReset();
}
