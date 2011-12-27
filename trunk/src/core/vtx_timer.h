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

#ifndef VTX_TIMER_H
#define VTX_TIMER_H

#include <core/vtx_buildconfig.h>
#include <core/vtx_atomic.h>
#include <core/vtx_assertions.h>

#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

namespace core
{
	class Timer
	{
	public:
		static U64_t readHighResolutionTimer()
					{

			core::U64_t result;
#if defined(VTX_PLATFORM_WIN32)
			LARGE_INTEGER value;
			BOOL success = QueryPerformanceCounter(&value);
			ASSERT(success);
			result = value.QuadPart;
#elif defined(VTX_PLATFORM_LINUX)
			result = 0; // PLACEHOLDER FOR LINUX VARIANT
#endif
			return result;
		}

		static inline U64_t readHighResolutionTimerFrequency()
		{
			core::U64_t result;
#if defined(VTX_PLATFORM_WIN32)
			LARGE_INTEGER value;
			BOOL success = QueryPerformanceFrequency(&value);
			ASSERT(success)
			result = value.QuadPart;
#elif defined(VTX_PLATFORM_LINUX)
			result = 0; // PLACEHOLDER FOR LINUX VARIANT
#endif
			return result;
		}
	};
}

#endif
