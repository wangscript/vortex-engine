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

#include "..\include\vtx_types.h"

using namespace core;

Vector4::Vector4( F32 x, F32 y, F32 z, F32 w )
{
	this->values[0] = x;
	this->values[1] = y;
	this->values[2] = z;
	this->values[3] = w;
	//this->x = x;
	//this->y = y;
	//this->z = z;
	//this->w = w;
}

void Vector4::add( Vector4 &other, Vector4 &result )
{
	//result.x = this->x + other.x;
	//result.y = this->y + other.y;
	//result.z = this->z + other.z;
	//result.w = this->w + other.w;
}

void Vector4::subtract( Vector4 &other, Vector4 &result )
{
	//result.x = this->x - other.x;
	//result.y = this->y - other.y;
	//result.z = this->z - other.z;
	//result.w = this->w - other.w;
}

void Vector4::multiply( Vector4 &other, Vector4 &result )
{
	//result.x = this->x * other.x;
	//result.y = this->y * other.y;
	//result.z = this->z * other.z;
	//result.w = this->w * other.w;
}

void Vector4::multiply( F32 value, Vector4 &result )
{
	//result.x = this->x * value;
	//result.y = this->y * value;
	//result.z = this->z * value;
	//result.w = this->w * value;
}