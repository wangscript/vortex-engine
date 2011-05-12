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

#include <core\vtx_types.h>

using namespace core;
using namespace platform;

Vector3::Vector3( F32 x, F32 y, F32 z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::add( Vector3 &other, Vector3 &result )
{
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;
}

void Vector3::subtract( Vector3 &other, Vector3 &result )
{
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	result.z = this->z - other.z;
}

//void Vector3::lerp( Vector3 &other, Vector3 &result, F32 amount )
//{
//	result.x = this->x + ((other.x - this->x) * amount);
//	result.y = this->y + ((other.y - this->y) * amount);
//	result.z = this->z + ((other.z - this->z) * amount);
//}

void Vector3::multiply( Vector3 &other, Vector3 &result )
{
	result.x = this->x * other.x;
	result.y = this->y * other.y;
	result.z = this->z * other.z;
}

void Vector3::multiply( F32 value, Vector3 &result )
{
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;
}
