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
#include <string>

namespace platform
{

#ifdef WIN32
	#include <Windows.h>
	typedef HANDLE SYSTEM_HANDLE;
	//TODO: Figure out why this #define can not be used anywhere without compile errors...
	#define INVALID_SYSTEM_HANDLE INVALID_HANDLE_VALUE;
#endif

#define U32_SIGNIFICANT_BIT 2147483648

	typedef unsigned char U8;
	typedef signed char I8;
	typedef unsigned short U16;
	typedef signed short I16;
	typedef unsigned int U32;
	typedef signed int I32;
	typedef signed long long I64;
	typedef unsigned long long U64;
	typedef float F32;

}

#endif