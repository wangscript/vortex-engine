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

#include "gtest/gtest.h"
#include "core/vtx_matrix4x4.h"
#include "core/vtx_vector3.h"
#include "core/vtx_vector4.h"
#include "core/vtx_math.h"

TEST(Vector4, DotCalculation)
{
	core::Vector4 v1(1, 2, 3, 4);
	core::Vector4 v2(5, 6, 7, 8);
	core::F32_t dot = core::Math::dot(v1, v2);
	ASSERT_EQ(dot, 70);
}

TEST(Matrix, MatrixMultiplication)
{
	core::F32_t valuesA[4][4];
	core::F32_t valuesB[4][4];
	core::F32_t valueA = 0;
	core::F32_t valueB = 15;

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

TEST(Matrix, CreateViewMatrix)
{
	core::Vector3 pos(15.5f, 0.0f, -23.1f);
	core::Vector3 target(1.0f, 20.4f, -1.0f);
	core::Vector3 up(0, 1, 0);
	core::Matrix4x4 *result = core::Matrix4x4::createViewMatrix(pos, target, up);

	ASSERT_EQ(result->m[0][0], -0.83610213f);
	ASSERT_EQ(result->m[0][1], 0.33516821f);
	ASSERT_EQ(result->m[0][2], 0.43427581f);
	ASSERT_EQ(result->m[0][3], 0.0f);
	ASSERT_EQ(result->m[1][0], 0.0f);
	ASSERT_EQ(result->m[1][1], 0.79164517f);
	ASSERT_EQ(result->m[1][2], -0.61098111f);
	ASSERT_EQ(result->m[1][3], 0.0f);
	ASSERT_EQ(result->m[2][0], -0.54857379f);
	ASSERT_EQ(result->m[2][1], -0.51084262f);
	ASSERT_EQ(result->m[2][2], -0.66189623f);
	ASSERT_EQ(result->m[2][3], 0.0f);
	ASSERT_EQ(result->m[3][0], 0.28752804f);
	ASSERT_EQ(result->m[3][1], -16.995571f);
	ASSERT_EQ(result->m[3][2], -22.021078f);
	ASSERT_EQ(result->m[3][3], 1.0f);
}

TEST(Matrix, CreateProjectionMatrix)
{
	core::F32_t fov = 1.75f;
	core::F32_t nearPlane = 0.1f;
	core::F32_t farPlane = 1000.0f;
	core::F32_t aspectRatio = 1920.0f / 1080.0f;

	core::Matrix4x4 *result = core::Matrix4x4::createProjection(fov, aspectRatio, nearPlane, farPlane);

	ASSERT_EQ(result->m[0][0], 0.46975935f);
	ASSERT_EQ(result->m[0][1], 0.0f);
	ASSERT_EQ(result->m[0][2], 0.0f);
	ASSERT_EQ(result->m[0][3], 0.0f);
	ASSERT_EQ(result->m[1][0], 0.0f);
	ASSERT_EQ(result->m[1][1], 0.83512771f);
	ASSERT_EQ(result->m[1][2], 0.0f);
	ASSERT_EQ(result->m[1][3], 0.0f);
	ASSERT_EQ(result->m[2][0], 0.0f);
	ASSERT_EQ(result->m[2][1], 0.0f);
	ASSERT_EQ(result->m[2][2], -1.0001000f);
	ASSERT_EQ(result->m[2][3], -1.0000000f);
	ASSERT_EQ(result->m[3][0], 0.0f);
	ASSERT_EQ(result->m[3][1], 0.0f);
	ASSERT_EQ(result->m[3][2], -0.10000000f);
	ASSERT_EQ(result->m[3][3], 0.0f);
}