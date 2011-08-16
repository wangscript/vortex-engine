#ifndef VTX_VECTOR3_H
#define VTX_VECTOR3_H

#include <platform/vtx_atomic.h>

namespace core
{
	class Vector3
	{
	public:
		Vector3();
		Vector3( core::F32_t x, core::F32_t y, core::F32_t z );
		void add( Vector3 &other, Vector3 &result );
		void cross( Vector3 &other, Vector3 &result );
		static core::F32_t dot( Vector3 &a, Vector3 &b );
		void subtract( Vector3 &other, Vector3 &result );
		void lerp( Vector3 &other, Vector3 &result, core::F32_t amount );
		void multiply( Vector3 &other, Vector3 &result );
		void multiply( core::F32_t value, Vector3 &result );
		void normalize( void );
		bool operator==(const Vector3 &other) const;
		bool operator!=(const Vector3 &other) const;
		Vector3 &operator=(const Vector3 &other);

		core::F32_t x;
		core::F32_t y;
		core::F32_t z;
	private:
	};
}

#endif