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
#include <cstring>

using namespace core;
using namespace platform;

Vector4::Vector4()
{
	memset(this->values, 0, sizeof(this->values));
}

Vector4::Vector4( F32 x, F32 y, F32 z, F32 w )
{
	this->values[0] = x;
	this->values[1] = y;
	this->values[2] = z;
	this->values[3] = w;
}

void Vector4::add( Vector4 &a, Vector4 &b, Vector4 &result )
{
	__m128 mA = _mm_load_ps(a.values);
	__m128 mB = _mm_load_ps(b.values);
	__m128 mRes = _mm_add_ps(mA, mB);
	_mm_store_ps(result.values, mRes);
}

void Vector4::subtract( Vector4 &a, Vector4 &b, Vector4 &result )
{
	__m128 mA = _mm_load_ps(a.values);
	__m128 mB = _mm_load_ps(b.values);
	__m128 mRes = _mm_sub_ps(mA, mB);
	_mm_store_ps(result.values, mRes);
}

void Vector4::multiply( Vector4 &a, Vector4 &b, Vector4 &result )
{
	__m128 mA = _mm_load_ps(a.values);
	__m128 mB = _mm_load_ps(b.values);
	__m128 mRes = _mm_mul_ps(mA, mB);
	_mm_store_ps(result.values, mRes);
}

void Vector4::multiply( Vector4 &a, F32 value, Vector4 &result )
{
	ALIGNED_16 F32 values[] = {value, value, value, value};
	__m128 mA = _mm_load_ps(a.values);
	__m128 mB = _mm_load_ps(values);
	__m128 mRes = _mm_mul_ps(mA, mB);
	_mm_store_ps(result.values, mRes);
}

F32 Vector4::dot( Vector4 &a, Vector4 &b )
{
	__m128 ma;
	__m128 mb;
	//__m128 mr;
	ma = _mm_load_ps(&a.values[0]);
	mb = _mm_load_ps(&b.values[0]);
	ALIGNED_16 F32 res[4];

	ma = _mm_mul_ps(ma, mb);
	ma = _mm_hadd_ps(ma, ma);
	ma = _mm_hadd_ps(ma, ma);
	// TODO: Replace this with intrinsics, even if the assembly code is awesome.
	// DONE!
	//__asm
	//{
	//	movaps xmm0, xmmword ptr [ma]
	//	movaps xmm1, xmmword ptr [mb]
	//	mulps xmm0, xmm1
	//	haddps xmm0, xmm0
	//	haddps xmm0, xmm0
	//	movaps xmmword ptr [mr], xmm0
	//}
	//_mm_store_ps(&res[0], mr);
	_mm_store_ps(&res[0], ma);
	return res[0];
}
