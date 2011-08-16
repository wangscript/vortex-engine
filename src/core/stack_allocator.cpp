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
//Foundaion, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <core/vtx_stack_allocator.h>
#include <core/vtx_assertions.h>
#include <stdlib.h>

core::StackAllocator::StackAllocator( core::U32_t stackSize )
{
	/*this->stackSize = stackSize;
	this->data = (U8*)malloc(this->stackSize);
	this->stackPosition = reinterpret_cast<__UINT64>(this->data);*/
}

core::StackAllocator::~StackAllocator()
{
	free(this->data);
}


core::StackAllocator::ErrorCode core::StackAllocator::allocate( core::U32_t size, core::U8_t **allocatedSpace )
{
	//ASSERT(size > 0);
	core::StackAllocator::ErrorCode err;
	err = core::StackAllocator::OK;
	/*U32 newStackPosition = this->stackPosition + size;
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
	// TODO: Uncomment this.
	return err;
}

void core::StackAllocator::freeToMarker( core::U32_t marker )
{
	/*ASSERT(marker > (U32)this->data);
	this->stackPosition = marker;*/
}

core::U32_t core::StackAllocator::getMarker()
{
	return this->stackPosition;
}
