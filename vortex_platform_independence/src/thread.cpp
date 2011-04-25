//Copyright (C) 2011 Emil Nordén
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "vtx_defineconfig.h"
#include "vtx_thread.h"
#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

using namespace platform;

Thread::Thread(ThreadFunc func)
{
	this->func = func;
}

Thread::ErrorCode Thread::start(void *threadData, U32 affinityMask)
{
	Thread::ErrorCode ret;
#if defined(VTX_PLATFORM_WIN32)
	this->handle = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)func,
		threadData,
		CREATE_SUSPENDED,
		NULL);

	if(handle == NULL)
	{
		// TODO: Check error codes here...
		int err = GetLastError();
		ret = Thread::UNKNOWN_ERROR;
	}
	else
	{
		if(SetThreadAffinityMask(this->handle, affinityMask) == 0)
		{
			// TODO: Check error codes here...
			int err = GetLastError();
			ret = Thread::UNKNOWN_ERROR;
		}
		else
		{
			ret = Thread::OK;
		}
	}
#elif defined(VTX_PLATFORM_LINUX)
	// TODO: IMPLEMENT LINUX VERSION
	ret = Thread::UNKNOWN_ERROR;
#endif
	return ret;
}

Thread::ErrorCode Thread::start(void *threadData)
{
	Thread::ErrorCode ret;
#if defined(VTX_PLATFORM_WIN32)
	this->handle = CreateThread(
		NULL,
		0,
		(LPTHREAD_START_ROUTINE)func,
		threadData,
		0,
		NULL);

	if(handle == NULL)
	{
		// TODO: Check error codes here...
		int err = GetLastError();
		ret = Thread::UNKNOWN_ERROR;
	}
	else
	{
		ret = Thread::OK;
	}
#elif defined(VTX_PLATFORM_LINUX)
	// TODO: IMPLEMENT LINUX VERSION
	ret = Thread::UNKNOWN_ERROR;
#endif
	return ret;
}
