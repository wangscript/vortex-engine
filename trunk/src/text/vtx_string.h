#ifndef VTX_STRING_H
#define VTX_STRING_H

#include <core/vtx_allocator.h>
#include <core/vtx_assertions.h>
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
		core::U8_t *buffer;
		core::U32_t bufferSize;
	public:
		String(core::Allocator &allocator);
		String(core::Allocator &allocator, const core::U8_t *string);
		String(core::Allocator &allocator, const core::U8_t *string , core::U32_t length);
		~String();

		const core::U8_t *getU8Data() { return this->buffer; }
		const char *getCharData() { return reinterpret_cast<const char*>(this->buffer); }

		const core::U8_t inline operator [] (int index)
		{
			ASSERT(index >= 0 && index < this->bufferSize);
			return this->buffer[index];
		}

		String& operator =(const core::U8_t *value)
		{
			core::U32_t size = strlen(reinterpret_cast<const char*>(value)) + 1;
			if(size != this->bufferSize)
			{
				this->buffer = static_cast<core::U8_t*>(this->alloc.reallocate(this->buffer, size));
				this->bufferSize = size;
			}
			memcpy(this->buffer, value, size);

			return *this;
		}
		
		String& operator =(const char *value)
		{
			core::U32_t size = strlen(reinterpret_cast<const char*>(value)) + 1;
			if(size != this->bufferSize)
			{
				this->buffer = static_cast<core::U8_t*>(this->alloc.reallocate(this->buffer, size));
			}
			memcpy(this->buffer, value, size);
		}
	};

}

#endif
