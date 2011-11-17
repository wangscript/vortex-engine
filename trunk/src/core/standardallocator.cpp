#include <core/vtx_standardallocator.h>

namespace core
{
	StandardAllocator::StandardAllocator()
	{
		this->totalSize = 0;
		this->allocations = 0;
	}

	void *StandardAllocator::allocate(core::U32_t size)
	{
		core::U32_t blockSize = size + sizeof(core::U32_t);
		void *ptr = malloc(blockSize);
		if(ptr)
		{
			core::U32_t *iptr = reinterpret_cast<core::U32_t*>(ptr);
			*iptr = blockSize;
			ptr = iptr + 1;

			this->allocations++;
			this->totalSize += blockSize;
		}

		return ptr;
	}

	void StandardAllocator::deallocate(void *ptr)
	{
		core::U32_t *iptr = reinterpret_cast<core::U32_t*>(ptr);
		core::U32_t blockSize = *--iptr;
		
		this->allocations--;
		this->totalSize -= blockSize;

		free(iptr);
	}

	core::U32_t StandardAllocator::allocatedSize()
	{
		return this->totalSize;
	}
}