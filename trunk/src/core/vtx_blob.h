#ifndef VTX_BLOB
#define VTX_BLOB

#include <core/vtx_atomic.h>

namespace core
{
	class Blob
	{
	private:
		void *ptr;
		core::U64_t size;
	public:
		Blob(void *pointer, core::U64_t dataSize);
		void *getPtr();
		core::U64_t getSize();
	};
}

#endif