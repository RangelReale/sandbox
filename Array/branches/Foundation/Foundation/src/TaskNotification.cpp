//
// TaskNotification.cpp
//
// $Id: //poco/svn/Foundation/src/TaskNotification.cpp#2 $
//
// Library: Foundation
// Package: Tasks
// Module:  Tasks
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


#include "Poco/TaskNotification.h"


namespace Poco {


TaskNotification::TaskNotification(Task* pTask):
	_pTask(pTask)
{
	if (_pTask) _pTask->duplicate();
}


TaskNotification::~TaskNotification()
{
	if (_pTask) _pTask->release();
}


TaskStartedNotification::TaskStartedNotification(Task* pTask):
	TaskNotification(pTask)
{
}

	
TaskStartedNotification::~TaskStartedNotification()
{
}


TaskCancelledNotification::TaskCancelledNotification(Task* pTask):
	TaskNotification(pTask)
{
}

	
TaskCancelledNotification::~TaskCancelledNotification()
{
}


TaskFinishedNotification::TaskFinishedNotification(Task* pTask):
	TaskNotification(pTask)
{
}

	
TaskFinishedNotification::~TaskFinishedNotification()
{
}


TaskFailedNotification::TaskFailedNotification(Task* pTask, const Exception& exc):
	TaskNotification(pTask),
	_pException(exc.clone())
{
}

	
TaskFailedNotification::~TaskFailedNotification()
{
	delete _pException;
}


TaskProgressNotification::TaskProgressNotification(Task* pTask, float progress):
	TaskNotification(pTask),
	_progress(progress)
{
}

	
TaskProgressNotification::~TaskProgressNotification()
{
}


} // namespace Poco
