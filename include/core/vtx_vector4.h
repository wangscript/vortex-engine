#ifndef VTX_VECTOR4_H
#define VTX_VECTOR4_H

#include <platform/vtx_atomic.h>

namespace core
{
	class Vector4
	{
	public:
		Vector4();
		Vector4( core::F32_t x, core::F32_t y, core::F32_t z, core::F32_t w );
		static void add( Vector4 &a, Vector4 &b, Vector4 &result );
		static void subtract( Vector4 &a, Vector4 &b, Vector4 &result );
		static void multiply( Vector4 &a, Vector4 &b, Vector4 &result );
		static void multiply( Vector4 &a, core::F32_t value, Vector4 &result );
		static core::F32_t dot( Vector4 &a, Vector4 &b );
		ALIGNED_16 core::F32_t values[4];
	private:
	};
}

#endif