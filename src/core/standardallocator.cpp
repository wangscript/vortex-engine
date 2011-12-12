#include <core/vtx_assertions.h>
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
		ASSERT(size > 0);
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
		
		ASSERT(blockSize <= this->totalSize);

		this->allocations--;
		this->totalSize -= blockSize;

		free(iptr);
	}

	core::U32_t StandardAllocator::allocatedSize()
	{
		return this->totalSize;
	}

	void *StandardAllocator::reallocate(void *ptr, core::U32_t size)
	{
		ASSERT(size > 0);
		core::U32_t blockSize = size + sizeof(core::U32_t);
		core::U32_t *iptr = static_cast<core::U32_t*>(ptr);
		core::U32_t originalSize = *--iptr;

		ASSERT(blockSize <= this->totalSize);

		iptr = static_cast<core::U32_t*>(realloc(iptr, blockSize));
		*iptr++ = blockSize;

		this->totalSize += blockSize - originalSize;

		return iptr;
	}
}