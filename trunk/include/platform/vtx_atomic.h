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

#ifndef VTX_ATOMIC_H
#define VTX_ATOMIC_H
#include <platform/vtx_defineconfig.h>
#include <string>
#ifdef WIN32
#include <Windows.h>
#endif

namespace platform
{

#if defined(VTX_PLATFORM_WINDOW)
	typedef HWND WINDOW;
	typedef HANDLE SYSTEM_HANDLE;
	//TODO: Figure out why this #define can not be used anywhere without compile errors...
	#define INVALID_SYSTEM_HANDLE INVALID_HANDLE_VALUE;
#endif
#if defined(VTX_PLATFORM_LINUX)
	//TODO: get this fixed.
	typedef void *WINDOW;
	typedef void *SYSTEM_HANDLE;
#endif

#define U32_SIGNIFICANT_BIT (1 << 31)
#if defined (VTX_PLATFORM_LINUX)
	typedef unsigned char		U8;
	typedef signed char			I8;
	typedef unsigned short		U16;
	typedef signed short		I16;
	typedef unsigned int		U32;
	typedef signed int			I32;
	typedef unsigned long long	U64;
	typedef float				F32;
#endif
#if defined(VTX_PLATFORM_WIN32)
	typedef unsigned __int8		U8;
	typedef signed __int8		I8;
	typedef unsigned __int16	U16;
	typedef signed __int16		I16;
	typedef unsigned __int32	U32;
	typedef signed __int32		I32;
	typedef unsigned __int64	U64;
	typedef float				F32;
#endif
#if defined(VTX_PLATFORM_LINUX)
	// Workaround until I find out how to get 64 bit integers on unix with g++.
	
#endif
	

}

#endif
