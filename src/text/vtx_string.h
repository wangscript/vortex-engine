#ifndef VTX_STRING_H
#define VTX_STRING_H

#include <core/vtx_atomic.h>

namespace core
{
	class Allocator;
}

namespace text
{
	class String
	{
	private:
		core::Allocator &alloc;
		core::U8_t *data;
	public:
		String(core::Allocator &allocator, const core::U8_t *string);
		String(core::Allocator &allocator, const core::U8_t *string , core::U32_t length);
		~String();

		const core::U8_t *getU8Data();
		const char *getCharData();
	};

}

#endif
