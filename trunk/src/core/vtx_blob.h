#ifndef VTX_BLOB
#define VTX_BLOB

#include <core/vtx_atomic.h>

namespace core
{
	class Blob
	{
	private:
		const void *ptr;
		core::U64_t size;
	public:
		Blob(const void *pointer, core::U64_t dataSize);
		const void *getPtr();
		core::U64_t getSize();
	};
}

#endif