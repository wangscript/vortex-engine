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

#ifndef VTX_MATRIX4x4_H
#define VTX_MATRIX4x4_H

#include <core/vtx_buildconfig.h>
#include <core/vtx_atomic.h>

namespace core
{
	class Vector3;

	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4( core::F32_t m[4][4] );
		static void multiply(Matrix4x4 &a, Matrix4x4 &b, Matrix4x4 &result );
		static Matrix4x4 *createViewMatrix(core::Vector3 &position, core::Vector3 &target, Vector3 &up);
		static void createViewMatrix(core::Vector3 &position, Vector3 &target, Vector3 &up, Matrix4x4 &result);
		static Matrix4x4 *createProjection(core::F32_t fov, core::F32_t aspectRatio, core::F32_t nearPlane, core::F32_t farPlane);
		static void createProjection(core::F32_t fov, core::F32_t aspectRatio, core::F32_t nearPlane, core::F32_t farPlane, Matrix4x4 &result);
		ALIGNED_16 core::F32_t m[4][4];
	private:
	};
}

#endif