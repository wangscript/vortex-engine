//Copyright (C) 2011 Emil Nordén
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include "vtx_stack_allocator.h"
#include "vtx_assertions.h"
#include <stdlib.h>

using namespace platform;

using namespace core;

StackAllocator::StackAllocator( U32 stackSize )
{
	/*this->stackSize = stackSize;
	this->data = (U8*)malloc(this->stackSize);
	this->stackPosition = reinterpret_cast<__UINT64>(this->data);*/
}

StackAllocator::~StackAllocator()
{
	free(this->data);
}


StackAllocator::ErrorCode StackAllocator::allocate( U32 size, U8 **allocatedSpace )
{
	/*ASSERT(size > 0);
	StackAllocator::ErrorCode err;
	U32 newStackPosition = this->stackPosition + size;
	U8 *stackAllocation = NULL;
	if(newStackPosition >
		((U32)this->data + this->stackSize))
	{
		// Insufficient stack space
		err = StackAllocator::NOT_ENOUGH_STACK_SPACE;
	}
	else
	{
		stackAllocation = (U8*)this->stackPosition;
		this->stackPosition = newStackPosition;
		err = StackAllocator::OK;
	}
	*allocatedSpace = stackAllocation;
	return err;*/
}

void StackAllocator::freeToMarker( U32 marker )
{
	/*ASSERT(marker > (U32)this->data);
	this->stackPosition = marker;*/
}

U32 StackAllocator::getMarker()
{
	return this->stackPosition;
}
