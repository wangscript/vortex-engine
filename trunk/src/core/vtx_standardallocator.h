#ifndef VTX_STANDARDALLOCATOR_H
#define VTX_STANDARDALLOCATOR_H

#include <core/vtx_allocator.h>
#include <core/vtx_atomic.h>

namespace core
{
	class StandardAllocator : public Allocator
	{
	private:
		core::U32_t totalSize;
		core::U32_t allocations;
	public:
		StandardAllocator();
		void *allocate(core::U32_t size);
		core::U32_t allocatedSize();
		void deallocate(void *p);
		
		void *reallocate(void *ptr, core::U32_t size);
	};
}

#endif