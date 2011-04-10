#include "vtx_thread.h"
#include <Windows.h>

using namespace platform;

Thread::Thread(ThreadFunc func)
{
	this->func = func;
}

Thread::ErrorCode Thread::start(void *threadData, U32 affinityMask)
{
	Thread::ErrorCode ret;
#ifdef WIN32
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
		ret = Thread::ErrorCode::UNKNOWN_ERROR;
	}
	else
	{
		if(SetThreadAffinityMask(this->handle, affinityMask) == 0)
		{
			// TODO: Check error codes here...
			int err = GetLastError();
			ret = Thread::ErrorCode::UNKNOWN_ERROR;
		}
		else
		{
			ret = Thread::ErrorCode::OK;
		}
	}
#endif
	return ret;
}

Thread::ErrorCode Thread::start(void *threadData)
{
	Thread::ErrorCode ret;
#ifdef WIN32
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
		ret = Thread::ErrorCode::UNKNOWN_ERROR;
	}
	else
	{
		ret = Thread::ErrorCode::OK;
	}
#endif
	return ret;
}