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

#include <platform/vtx_defineconfig.h>
#include <core/vtx_types.h>

#include <xmmintrin.h>
#include <pmmintrin.h>

using namespace core;
using namespace platform;

Vector3::Vector3()
{
	this->x = this->y = this->z = 0;
}

Vector3::Vector3( F32_t x, F32_t y, F32_t z )
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

void Vector3::multiply( F32_t value, Vector3 &result )
{
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;
}

void Vector3::normalize(void)
{
	// Must pad with a trailing 0, to store in 128-bit register
	ALIGNED_16 float vector[] = {this->x, this->y, this->z, 0};
	__m128 simdvector;
	__m128 result;
	simdvector = _mm_load_ps(vector);
	
	// (X^2, Y^2, Z^2, 0^2)
	result = _mm_mul_ps(simdvector, simdvector);

	// Add all elements together, giving us (X^2 + Y^2 + Z^2 + 0^2)
	result = _mm_hadd_ps(result, result);
	result = _mm_hadd_ps(result, result);
	
	// Calculate square root, giving us sqrt(X^2 + Y^2 + Z^2 + 0^2)
	result = _mm_sqrt_ps(result);

	// Calculate reciprocal, giving us 1 / sqrt(X^2 + Y^2 + Z^2 + 0^2)
	result = _mm_rcp_ps(result);

	// Finally, multiply the result with our original vector.
	simdvector = _mm_mul_ps(simdvector, result);

	_mm_store_ps(vector, simdvector);

	this->x = vector[0];
	this->y = vector[1];
	this->z = vector[2];
}