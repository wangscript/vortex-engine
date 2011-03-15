//Copyright (c) 2011, Emil Nordén
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "..\include\vtx_types.h"
#include "..\include\vtx_math.h"
#include <xmmintrin.h>
#include <cstring>

/* Credits goes to Jason Gregory for these convenient macros */
#define SHUFFLE_PARAM(x, y, z ,w) \
	((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))
#define _mm_replicate_x_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))
#define _mm_replicate_y_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))
#define _mm_replicate_z_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))
#define _mm_replicate_w_ps(v) \
	_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(3, 3, 3, 3))

using namespace core;

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
	b0.m128_i64[0] = b0.m128_i64[1] = 1;
	b1.m128_i64[0] = b1.m128_i64[1] = 1;
	b2.m128_i64[0] = b2.m128_i64[1] = 1;
	b3.m128_i64[0] = b3.m128_i64[1] = 1;
	
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