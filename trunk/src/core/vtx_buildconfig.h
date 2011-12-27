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

#ifndef VTX_BUILDCONFIG_H
#define VTX_BUILDCONFIG_H

#define VTX_VER		"0.1"

#if defined(WIN32)
#define VTX_PLATFORM_WIN32

#define cpuid(func,a,b,c,d)\
	asm {\
	mov	eax, func\
	cpuid\
	mov	a, eax\
	mov	b, ebx\
	mov	c, ecx\
	mov	d, edx\
	}

#elif defined(__linux)
#define VTX_PLATFORM_LINUX

#define cpuid(func,ax,bx,cx,dx)\
	__asm__ __volatile__ ("cpuid":\
	"=a" (ax), "=b" (bx), "=c" (cx), "=d" (dx) : "a" (func));

#endif

// Debug flag
#if defined(VTX_PLATFORM_WIN32)
#if defined(_DEBUG) || defined(DEBUG)
#define VTX_DEBUG
#endif
#endif
#if defined(VTX_PLATFORM_LINUX)
#if !defined(NDEBUG)
#define VTX_DEBUG
#endif
#endif


/*	Render API defines
	Comment out a define to not include it in the build. */
#if defined(VTX_PLATFORM_WIN32)
#define VTX_COMPILE_WITH_DX10
//#define VTX_COMPILE_WITH_DX11
#define VTX_COMPILE_WITH_OPENGL

#elif defined(VTX_PLATFORM_LINUX)
#define VTX_COMPILE_WITH_OPENGL
#endif

#if defined(VTX_COMPILE_WITH_DX10)
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D3D10.lib")
#endif

#if defined(VTX_COMPILE_WITH_OPENGL) && defined(VTX_PLATFORM_WIN32)
#pragma comment(lib, "opengl32.lib")
#endif

#if defined(VTX_PLATFORM_WIN32)
#define ALIGNED_16 __declspec(align(16))
#define ALIGNED_32 __declspec(align(32))
#elif defined(VTX_PLATFORM_LINUX)
#define ALIGNED_16 __attribute__((aligned(16)))
#define ALIGNED_32 __attribute__((aligned(32)))
#endif

#define VTX_USE_SSE 1
//#define VTX_USE_AVX 1

#define VTX_ASSERTIONS_ENABLED

#endif