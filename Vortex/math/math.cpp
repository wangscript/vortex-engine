//Copyright (c) 2011, Emil Nordén
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "..\include\vtx_math.h"
#include <xmmintrin.h>

using namespace core;

void Math::cross(Vector3 &a, Vector3 &b, Vector3 &result)
{
	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
}

F32 Math::dot(Vector2 &a, Vector2 &b)
{
	return (a.x * b.x + 
			a.y * b.y);
}

F32 Math::dot(Vector3 &a, Vector3 &b)
{
	return (a.x * b.x +
			a.y * b.y +
			a.z * b.z);
}

F32 Math::dot(Vector4 &a, Vector4 &b)
{
	__m128 ma;
	__m128 mb;
	__m128 mr;
	ma = _mm_load_ps(&a.values[0]);
	mb = _mm_load_ps(&b.values[0]);
	__declspec(align(16)) F32 res[4];
	__asm
	{
		movaps xmm0, xmmword ptr [ma]
		movaps xmm1, xmmword ptr [mb]
		mulps xmm0, xmm1
		haddps xmm0, xmm0
		haddps xmm0, xmm0
		movaps xmmword ptr [mr], xmm0
	}
	_mm_store_ps(&res[0], mr);
	return res[0];
	
	//return (a.values[0] * b.values[0] +
	//		a.values[1] * b.values[1] +
	//		a.values[2] * b.values[2] +
	//		a.values[3] * b.values[3]);
}