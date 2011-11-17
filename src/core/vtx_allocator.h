#ifndef VTX_ALLOCATOR_H
#define VTX_ALLOCATOR_H

#include <core/vtx_atomic.h>

class Allocator
{
public:
	virtual void *allocate(core::U32_t size) = 0;
	virtual void deallocate(void *p) = 0;
	virtual core::U32_t allocatedSize() = 0;
};

#endif