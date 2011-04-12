#ifndef VTX_THREAD_H
#define VTX_THREAD_H

#include "vtx_atomic.h"

namespace platform
{
	typedef U32 (*ThreadFunc)(void*);

	class Thread
	{
	public:
		enum ErrorCode { OK, UNKNOWN_ERROR };
		explicit Thread(ThreadFunc func);
		ErrorCode start(void *threadData);
		ErrorCode start(void *threadData, U32 affinityMask);
	private:
		SYSTEM_HANDLE handle;
		ThreadFunc func;
	};
}

#endif