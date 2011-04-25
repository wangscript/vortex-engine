//Copyright (C) 2011 Emil Nord�n
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
#include <string>
#ifdef WIN32
#include <Windows.h>
#endif

namespace platform
{

#ifdef WIN32
	typedef HWND WINDOW;
	typedef HANDLE SYSTEM_HANDLE;
	//TODO: Figure out why this #define can not be used anywhere without compile errors...
	#define INVALID_SYSTEM_HANDLE INVALID_HANDLE_VALUE;
#else
	//TODO: get this fixed.
	typedef void *WINDOW;
	typedef void *SYSTEM_HANDLE;
#endif

#define U32_SIGNIFICANT_BIT 2147483648

	typedef unsigned char U8;
	typedef signed char I8;
	typedef unsigned short U16;
	typedef signed short I16;
	typedef unsigned int U32;
	typedef signed int I32;
#ifdef WIN32
	typedef unsigned long long U64;
#else
	// Workaround until I find out how to get 64 bit integers on unix with g++.
	typedef unsigned long U64;
#endif
	typedef float F32;

}

#endif
