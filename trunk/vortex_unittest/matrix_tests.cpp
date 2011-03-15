//Copyright (c) 2011, Emil Nordén
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "gtest/gtest.h"
#include "..\Vortex\include\vtx_types.h"
#include "..\Vortex\include\vtx_math.h"

TEST(Vector4, DotCalculation)
{
	core::Vector4 v1(1, 2, 3, 4);
	core::Vector4 v2(5, 6, 7, 8);
	F32 dot = core::Math::dot(v1, v2);
	ASSERT_EQ(dot, 70);
}

TEST(Matrix, MatrixMultiplication)
{
	F32 valuesA[4][4];
	F32 valuesB[4][4];
	F32 valueA = 0;
	F32 valueB = 15;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			valuesA[i][j] = valueA;
			valuesB[i][j] = valueB;
			valueA++;
			valueB--;
		}
	}

	core::Matrix4x4 matrixA(valuesA);
	core::Matrix4x4 matrixB(valuesB);
	core::Matrix4x4 result;
	core::Matrix4x4::multiply(matrixA, matrixB, result);
	ASSERT_EQ(result.m[0][0], 34);
	ASSERT_EQ(result.m[0][1], 28);
	ASSERT_EQ(result.m[0][2], 22);
	ASSERT_EQ(result.m[0][3], 16);
	ASSERT_EQ(result.m[1][0], 178);
	ASSERT_EQ(result.m[1][1], 156);
	ASSERT_EQ(result.m[1][2], 134);
	ASSERT_EQ(result.m[1][3], 112);
	ASSERT_EQ(result.m[2][0], 322);
	ASSERT_EQ(result.m[2][1], 284);
	ASSERT_EQ(result.m[2][2], 246);
	ASSERT_EQ(result.m[2][3], 208);
	ASSERT_EQ(result.m[3][0], 466);
	ASSERT_EQ(result.m[3][1], 412);
	ASSERT_EQ(result.m[3][2], 358);
	ASSERT_EQ(result.m[3][3], 304);
}