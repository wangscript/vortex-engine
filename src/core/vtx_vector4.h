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

#ifndef VTX_VECTOR4_H
#define VTX_VECTOR4_H

#include <core/vtx_atomic.h>

namespace core
{
	class Vector4
	{
	public:
		Vector4();
		Vector4( core::F32_t x, core::F32_t y, core::F32_t z, core::F32_t w );
		static void add( Vector4 &a, Vector4 &b, Vector4 &result );
		static void subtract( Vector4 &a, Vector4 &b, Vector4 &result );
		static void multiply( Vector4 &a, Vector4 &b, Vector4 &result );
		static void multiply( Vector4 &a, core::F32_t value, Vector4 &result );
		static core::F32_t dot( Vector4 &a, Vector4 &b );
		ALIGNED_16 core::F32_t values[4];
	private:
	};
}

#endif