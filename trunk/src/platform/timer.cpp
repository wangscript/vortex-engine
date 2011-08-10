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

#include <platform/vtx_timer.h>
#include <platform/vtx_defineconfig.h>
#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

using namespace platform;

U64_t Timer::readHighResolutionTimer(void)
{
	U64_t result;
#if defined(VTX_PLATFORM_WIN32)
	LARGE_INTEGER value;
	BOOL res = QueryPerformanceCounter(&value);
	//TODO: Handle res here.
	result = value.QuadPart;
#elif defined(VTX_PLATFORM_LINUX)
	result = 0; // PLACEHOLDER FOR LINUX VARIANT
#endif
	return result;
}

U64_t Timer::readHighResolutionTimerFrequency(void)
{
	U64_t result;
#if defined(VTX_PLATFORM_WIN32)
	LARGE_INTEGER value;
	BOOL res = QueryPerformanceFrequency(&value);
	//TODO: Handle res here.
	result = value.QuadPart;
#elif defined(VTX_PLATFORM_LINUX)
	result = 0; // PLACEHOLDER FOR LINUX VARIANT
#endif
	return result;
}
