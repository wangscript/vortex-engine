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

#include <core/vtx_buildconfig.h>
#include <core/vtx_vector3.h>

#include <emmintrin.h>
#include <xmmintrin.h>
//#include <intrin.h>
#include <pmmintrin.h>


core::Vector3::Vector3()
{
	this->x = this->y = this->z = 0;
}

core::Vector3::Vector3( core::F32_t x, core::F32_t y, core::F32_t z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void core::Vector3::add( core::Vector3 &other, core::Vector3 &result )
{
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;
}

void core::Vector3::subtract( core::Vector3 &other, core::Vector3 &result )
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

void core::Vector3::multiply( core::Vector3 &other, core::Vector3 &result )
{
	result.x = this->x * other.x;
	result.y = this->y * other.y;
	result.z = this->z * other.z;
}

void core::Vector3::multiply( core::F32_t value, core::Vector3 &result )
{
	result.x = this->x * value;
	result.y = this->y * value;
	result.z = this->z * value;
}

void core::Vector3::normalize(void)
{
#if defined(VTX_USE_AVX)
	ALIGNED_32 platform::F64_t vector[] = {this->x, this->y, this->z, 0};
	ALIGNED_32 platform::F64_t reciprocalVector[] = {1.0, 1.0, 1.0, 1.0};
	__m256d simdvector;
	__m256d result;
	__m256d recp;

	simdvector = _mm256_load_pd(vector);
	recp = _mm256_load_pd(reciprocalVector);

	result = _mm256_mul_pd(simdvector, simdvector);

	result = _mm256_hadd_pd(result, result);
	result = _mm256_hadd_pd(result, result);

	result = _mm256_sqrt_pd(result);

	result = _mm256_div_pd(recp, result);

	simdvector = _mm256_mul_pd(simdvector, result);

	_mm256_store_pd(vector, simdvector);

	this->x = vector[0];
	this->y = vector[1];
	this->z = vector[2];

#elif defined(VTX_USE_SSE)
	// Must pad with a trailing 0, to store in 128-bit register
	ALIGNED_16 core::F32_t vector[] = {this->x, this->y, this->z, 0};
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
#else
	core::F64_t num = 1.0 / std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2));
	this->x *= num;
	this->y *= num;
	this->z *= num;
#endif
}

void core::Vector3::cross( core::Vector3 &other, core::Vector3 &result )
{
	// TODO: Rewrite this using SIMD
	result.x = ((core::F64_t) this->y * (core::F64_t) other.z - (core::F64_t) this->z * (core::F64_t) other.y);
	result.y = ((core::F64_t) this->z * (core::F64_t) other.x - (core::F64_t) this->x * (core::F64_t) other.z);
	result.z = ((core::F64_t) this->x * (core::F64_t) other.y - (core::F64_t) this->y * (core::F64_t) other.x);
}

core::F32_t core::Vector3::dot( core::Vector3 &a, core::Vector3 &b )
{
	ALIGNED_16 core::F32_t aVector[] = {a.x, a.y, a.z, 0};
	ALIGNED_16 core::F32_t bVector[] = {b.x, b.y, b.z, 0};
	__m128 ma;
	__m128 mb;
	//__m128 mr;
	ma = _mm_load_ps(aVector);
	mb = _mm_load_ps(bVector);
	ALIGNED_16 core::F32_t res[4];

	ma = _mm_mul_ps(ma, mb);
	ma = _mm_hadd_ps(ma, ma);
	ma = _mm_hadd_ps(ma, ma);
	
	_mm_store_ps(&res[0], ma);
	return res[0];
}

bool core::Vector3::operator==(const Vector3 &other) const
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool core::Vector3::operator!=(const Vector3 &other) const
{
	return !(*this == other);
}

core::Vector3 &core::Vector3::operator=(const Vector3 &other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	return *this;
}
