#ifndef VTX_STANDARDALLOCATOR_H
#define VTX_STANDARDALLOCATOR_H

#include <core/vtx_allocator.h>
#include <core/vtx_atomic.h>

namespace core
{
	class StandardAllocator : Allocator
	{
	private:
		core::U32_t totalSize;
		core::U32_t allocations;
	public:
		StandardAllocator();
		void *allocate(core::U32_t size);
		void deallocate(void *p);
		core::U32_t allocatedSize();
	};
}

#endif