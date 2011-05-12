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

#ifndef VTX_TYPES_H
#define VTX_TYPES_H

#include <platform/vtx_defineconfig.h>
#include <platform/vtx_atomic.h>

namespace core
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4( platform::F32 m[4][4] );
		static void multiply(Matrix4x4 &a, Matrix4x4 &b, Matrix4x4 &result );
		ALIGNED_16 platform::F32 m[4][4];
	private:
	};

	template <class T>
	class Vector2
	{
	public:
		Vector2()
		{
		}

		Vector2( T x, T y )
		{
			this->x = x;
			this->y = y;
		}

		void add( Vector2 &other, Vector2 &result )
		{
			result.x = this->x + other.x;
			result.y = this->y + other.y;
		}

		void subtract( Vector2 &other, Vector2 &result )
		{
			result.x = this->x - other.x;
			result.y = this->y - other.y;
		}

		void lerp( Vector2 &other, Vector2 &result, T amount )
		{
			result.x = this->x + ((other.x - this->x) * amount);
			result.y = this->y + ((other.y - this->y) * amount);
		}

		void multiply( Vector2 &other, Vector2 &result )
		{
			result.x = this->x * other.x;
			result.y = this->y * other.y;
		}

		void multiply( T value, Vector2 &result )
		{
			result.x = this->x * value;
			result.y = this->y * value;
		}

		T x;
		T y;
	};

	class Vector3
	{
	public:
		Vector3();
		Vector3( platform::F32 x, platform::F32 y, platform::F32 z );
		void add( Vector3 &other, Vector3 &result );
		void subtract( Vector3 &other, Vector3 &result );
		void lerp( Vector3 &other, Vector3 &result, platform::F32 amount );
		void multiply( Vector3 &other, Vector3 &result );
		void multiply( platform::F32 value, Vector3 &result );
		platform::F32 x;
		platform::F32 y;
		platform::F32 z;
	private:
	};

	class Vector4
	{
	public:
		Vector4();
		Vector4( platform::F32 x, platform::F32 y, platform::F32 z, platform::F32 w );
		static void add( Vector4 &a, Vector4 &b, Vector4 &result );
		static void subtract( Vector4 &a, Vector4 &b, Vector4 &result );
		static void multiply( Vector4 &a, Vector4 &b, Vector4 &result );
		static void multiply( Vector4 &a, platform::F32 value, Vector4 &result );
		static platform::F32 dot( Vector4 &a, Vector4 &b );
		ALIGNED_16 platform::F32 values[4];
	private:
	};
}

#endif
