#ifndef VTX_MATRIX4x4_H
#define VTX_MATRIX4x4_H

#include <platform/vtx_buildconfig.h>
#include <platform/vtx_atomic.h>

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