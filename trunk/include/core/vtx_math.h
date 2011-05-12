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

#ifndef VTX_MATH_H
#define VTX_MATH_H

#include "vtx_types.h"

namespace core
{
	class Math
	{
	public:
		static void cross(Vector3 &a, Vector3 &b, Vector3 &result);
		template <class T>
		static platform::F32 dot(T &a, T &b)
		{
			return (a.x * b.x + 
				a.y * b.y);
		}
		static platform::F32 dot(Vector3 &a, Vector3 &b);
		static platform::F32 dot(Vector4 &a, Vector4 &b);
	};
}

#endif
