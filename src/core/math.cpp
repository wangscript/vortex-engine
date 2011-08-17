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
#include <core/vtx_math.h>
#include <core/vtx_vector3.h>
#include <core/vtx_vector4.h>
#include <xmmintrin.h>
#include <pmmintrin.h>

void core::Math::cross(core::Vector3 &a, core::Vector3 &b, core::Vector3 &result)
{
	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
}

core::F32_t core::Math::dot(core::Vector3 &a, core::Vector3 &b)
{
	return (a.x * b.x +
			a.y * b.y +
			a.z * b.z);
}

core::F32_t core::Math::dot(core::Vector4 &a, core::Vector4 &b)
{
	__m128 ma;
	__m128 mb;
	__m128 mr;
	ma = _mm_load_ps(&a.values[0]);
	mb = _mm_load_ps(&b.values[0]);
	ALIGNED_16 core::F32_t res[4];
	// TODO: Write asm macro.
	ma = _mm_mul_ps(ma, mb);
	ma = _mm_hadd_ps(ma, ma);
	ma = _mm_hadd_ps(ma, ma);
	
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
