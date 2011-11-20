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

#include <core/vtx_matrix4x4.h>
#include <core/vtx_vector3.h>
#include <core/vtx_math.h>
#include <xmmintrin.h>
#include <pmmintrin.h>
#include <cstring>
#include <cmath>


core::Matrix4x4::Matrix4x4( core::F32_t m[4][4] )
{
	memcpy(this->m, m, sizeof(core::F32_t) * 16);
}

core::Matrix4x4::Matrix4x4()
{
}

void core::Matrix4x4::multiply(core::Matrix4x4 &a, core::Matrix4x4 &b, core::Matrix4x4 &result )
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

core::Matrix4x4 *core::Matrix4x4::createViewMatrix(core::Vector3 &position, core::Vector3 &target, core::Vector3 &up)
{
	core::Vector3 direction;
	core::Vector3 cameraLocalXAxis;
	core::Vector3 vector;

	position.subtract(target, direction);
	direction.normalize();

	up.cross(direction, cameraLocalXAxis);
	cameraLocalXAxis.normalize();

	direction.cross(cameraLocalXAxis, vector);
	
	core::Matrix4x4 *result = new core::Matrix4x4();
	result->m[0][0] = cameraLocalXAxis.x;
	result->m[0][1] = vector.x;
	result->m[0][2] = direction.x;
	result->m[0][3] = 0.0f;
	result->m[1][0] = cameraLocalXAxis.y;
	result->m[1][1] = vector.y;
	result->m[1][2] = direction.y;
	result->m[1][3] = 0.0f;
	result->m[2][0] = cameraLocalXAxis.z;
	result->m[2][1] = vector.z;
	result->m[2][2] = direction.z;
	result->m[2][3] = 0.0f;
	result->m[3][0] = -core::Vector3::dot(cameraLocalXAxis, position);
	result->m[3][1] = -core::Vector3::dot(vector, position);
	result->m[3][2] = -core::Vector3::dot(direction, position);
	result->m[3][3] = 1.0f;
	return result;
}

void core::Matrix4x4::createViewMatrix(core::Vector3 &position, core::Vector3 &target, core::Vector3 &up, core::Matrix4x4 &result)
{
	core::Vector3 direction;
	core::Vector3 cameraLocalXAxis;
	core::Vector3 vector;

	position.subtract(target, direction);
	direction.normalize();

	up.cross(direction, cameraLocalXAxis);
	up.normalize();

	direction.cross(cameraLocalXAxis, vector);
	
	result.m[0][0] = cameraLocalXAxis.x;
	result.m[0][1] = vector.x;
	result.m[0][2] = direction.x;
	result.m[0][3] = 0.0f;
	result.m[1][0] = cameraLocalXAxis.y;
	result.m[1][1] = vector.y;
	result.m[1][2] = direction.y;
	result.m[1][3] = 0.0f;
	result.m[2][0] = cameraLocalXAxis.z;
	result.m[2][1] = vector.z;
	result.m[2][2] = direction.z;
	result.m[2][3] = 0.0f;
	result.m[3][0] = -core::Vector3::dot(cameraLocalXAxis, position);
	result.m[3][1] = -core::Vector3::dot(vector, position);
	result.m[3][2] = -core::Vector3::dot(direction, position);
	result.m[3][3] = 1.0f;
}

core::Matrix4x4 *core::Matrix4x4::createProjection(core::F32_t fov, core::F32_t aspectRatio, core::F32_t nearPlane, core::F32_t farPlane)
{
	core::F32_t val1 = 1.0f / std::tan(fov * 0.5f);
	core::F32_t val2 = val1 / aspectRatio;

	core::Matrix4x4 *matrix = new core::Matrix4x4();
	matrix->m[0][0] = val2;
	matrix->m[0][1] = 0.0f;
	matrix->m[0][2] = 0.0f;
	matrix->m[0][3] = 0.0f;
	
	matrix->m[1][0] = 0.0f;
	matrix->m[1][1] = val1;
	matrix->m[1][2] = 0.0f;
	matrix->m[1][3] = 0.0f;
	
	matrix->m[2][0] = 0.0f;
	matrix->m[2][1] = 0.0f;
	matrix->m[2][2] = farPlane / (nearPlane - farPlane);
	matrix->m[2][3] = -1.0f;

	matrix->m[3][0] = 0.0f;
	matrix->m[3][1] = 0.0f;
	matrix->m[3][2] = (core::F32_t)((core::F64_t) nearPlane * (core::F64_t) farPlane / ((core::F64_t) nearPlane - (core::F64_t) farPlane));
	matrix->m[3][3] = 0.0f;

	return matrix;
}

void core::Matrix4x4::createProjection(core::F32_t fov, core::F32_t aspectRatio, core::F32_t nearPlane, core::F32_t farPlane, core::Matrix4x4 &result)
{
	core::F32_t val1 = 1.0f / std::tan(fov * 0.5f);
	core::F32_t val2 = val1 / aspectRatio;

	result.m[0][0] = val2;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;
	
	result.m[1][0] = 0.0f;
	result.m[1][1] = val1;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;
	
	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = farPlane / (nearPlane - farPlane);
	result.m[2][3] = -1.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = (core::F32_t)((core::F64_t) nearPlane * (core::F64_t) farPlane / ((core::F64_t) nearPlane - (core::F64_t) farPlane));
	result.m[3][3] = 0.0f;
}
