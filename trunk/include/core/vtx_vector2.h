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

#ifndef VTX_VECTOR2_H
#define VTX_VECTOR2_H

namespace core
{
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
}

#endif