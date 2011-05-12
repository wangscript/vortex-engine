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

#ifndef VTX_THREAD_H
#define VTX_THREAD_H

#include <platform/vtx_defineconfig.h>
#include <platform/vtx_atomic.h>

#if defined(VTX_PLATFORM_WIN32)
typedef HANDLE THREAD_HANDLE;
typedef platform::U32 (*ThreadFunc)(void*);
#elif defined(VTX_PLATFORM_LINUX)
#include <pthread.h>
typedef pthread_t THREAD_HANDLE;
typedef void *(*ThreadFunc)(void*);
#endif


namespace platform
{

	class Thread
	{
	public:
		enum ErrorCode { OK, UNKNOWN_ERROR, NOPERMISSION, SYSTEMFAIL };
		explicit Thread(ThreadFunc func);
		ErrorCode start(void *threadData);
		ErrorCode start(void *threadData, U32 affinityMask);
	private:
		THREAD_HANDLE handle;
		ThreadFunc func;
	};
}

#endif
