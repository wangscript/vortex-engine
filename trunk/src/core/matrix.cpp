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
#include <core\vtx_math.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <cstring>

using namespace core;
using namespace platform;

Matrix4x4::Matrix4x4( F32 m[4][4] )
{
	memcpy(this->m, m, sizeof(F32) * 16);
}

Matrix4x4::Matrix4x4()
{
}

void Matrix4x4::multiply(Matrix4x4 &a, Matrix4x4 &b, Matrix4x4 &result )
{
	__m128 b0, b1, b2, b3;
	__m128 row, res;
	/*b0.m128_i64[0] = b0.m128_i64[1] = 1;
	b1.m128_i64[0] = b1.m128_i64[1] = 1;
	b2.m128_i64[0] = b2.m128_i64[1] = 1;
	b3.m128_i64[0] = b3.m128_i64[1] = 1;*/
	// Can not assign 1 as above when compiling using g++. memset works better.
	memset(&b0, 0, sizeof(b0));
	memset(&b1, 0, sizeof(b1));
	memset(&b2, 0, sizeof(b2));
	memset(&b3, 0, sizeof(b3));
	
	// Load all 4 columns.
	b0 = _mm_loadh_pi(_mm_loadl_pi(b0, (__m64*)&b.m[0][0]), (__m64*)&b.m[0][2]);
	b1 = _mm_loadh_pi(_mm_loadl_pi(b1, (__m64*)&b.m[1][0]), (__m64*)&b.m[1][2]);
	b2 = _mm_loadh_pi(_mm_loadl_pi(b2, (__m64*)&b.m[2][0]), (__m64*)&b.m[2][2]);
	b3 = _mm_loadh_pi(_mm_loadl_pi(b3, (__m64*)&b.m[3][0]), (__m64*)&b.m[3][2]);

	// Calculate first row.
	row = _mm_set_ps1(a.m[0][0]);
	res = _mm_mul_ps(row, b0);

	row = _mm_set_ps1(a.m[0][1]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b1));

	row = _mm_set_ps1(a.m[0][2]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b2));

	row = _mm_set_ps1(a.m[0][3]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b3));

	_mm_store_ps(&result.m[0][0], res);

	//Calculate second row
	row = _mm_set_ps1(a.m[1][0]);
	res = _mm_mul_ps(row, b0);

	row = _mm_set_ps1(a.m[1][1]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b1));

	row = _mm_set_ps1(a.m[1][2]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b2));

	row = _mm_set_ps1(a.m[1][3]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b3));

	_mm_store_ps(&result.m[1][0], res);

	//Calculate third row
	row = _mm_set_ps1(a.m[2][0]);
	res = _mm_mul_ps(row, b0);

	row = _mm_set_ps1(a.m[2][1]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b1));

	row = _mm_set_ps1(a.m[2][2]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b2));

	row = _mm_set_ps1(a.m[2][3]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b3));

	_mm_store_ps(&result.m[2][0], res);

	//Calculate fourth row
	row = _mm_set_ps1(a.m[3][0]);
	res = _mm_mul_ps(row, b0);

	row = _mm_set_ps1(a.m[3][1]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b1));

	row = _mm_set_ps1(a.m[3][2]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b2));

	row = _mm_set_ps1(a.m[3][3]);
	res = _mm_add_ps(res, _mm_mul_ps(row, b3));

	_mm_store_ps(&result.m[3][0], res);
}
