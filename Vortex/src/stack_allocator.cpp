#include "..\include\vtx_stack_allocator.h"
#include "..\include\vtx_assertions.h"
#include <stdlib.h>

using namespace core;

StackAllocator::StackAllocator( U32 stackSize )
{
	this->stackSize = stackSize;
	this->data = (U8*)malloc(this->stackSize);
	this->stackPosition = (U32)this->data;
}

StackAllocator::~StackAllocator()
{
	free(this->data);
}


StackAllocator::ErrorCode StackAllocator::allocate( U32 size, U8 **allocatedSpace )
{
	ASSERT(size > 0);
	StackAllocator::ErrorCode err;
	U32 newStackPosition = this->stackPosition + size;
	U8 *stackAllocation = NULL;
	if(newStackPosition >
		((U32)this->data + this->stackSize))
	{
		// Insufficient stack space
		err = StackAllocator::ErrorCode::NOT_ENOUGH_STACK_SPACE;
	}
	else
	{
		stackAllocation = (U8*)this->stackPosition;
		this->stackPosition = newStackPosition;
		err = StackAllocator::ErrorCode::OK;
	}
	*allocatedSpace = stackAllocation;
	return err;
}

void StackAllocator::freeToMarker( U32 marker )
{
	ASSERT(marker > (U32)this->data);
	this->stackPosition = marker;
}

U32 StackAllocator::getMarker()
{
	return this->stackPosition;
}