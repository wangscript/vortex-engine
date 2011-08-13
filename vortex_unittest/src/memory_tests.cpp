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

#include <core/vtx_stack_allocator.h>
#include "gtest/gtest.h"
#include <vortex/vtx_vortex.h>

#define STACKALLOCATOR_SIZE		2048
//h

TEST(StackAllocator, AllocationTest)
{
	core::StackAllocator stack(STACKALLOCATOR_SIZE);
	platform::U32_t* dataBlocks[STACKALLOCATOR_SIZE / 4];
	platform::U32_t *data;
	core::StackAllocator::ErrorCode err;
	platform::U32_t marker;
	
	/* Fill 50% of stack with integers */
	for(platform::U32_t i = 0; i < STACKALLOCATOR_SIZE / 8; i++)
	{
		err = (stack.allocate(4, (platform::U8_t**)&data));
		*data = i;
		dataBlocks[i] = data;
	}

	/* Get marker */
	marker = stack.getMarker();

	/* Fill 50% of stack with integers */
	for(platform::U32_t i = 0; i < STACKALLOCATOR_SIZE / 8; i++)
	{
		err = (stack.allocate(4, (platform::U8_t**)&data));
		*data = (STACKALLOCATOR_SIZE / 8) + i;
		dataBlocks[(STACKALLOCATOR_SIZE / 8) + i] = data;
	}

	/* Assert data integrity */
	for(platform::U32_t i = 0; i < STACKALLOCATOR_SIZE / 4; i++)
	{
		ASSERT_EQ(*dataBlocks[i], i);
	}

	/* Free to marker */
	stack.freeToMarker(marker);

	for(platform::U32_t i = 0; i < STACKALLOCATOR_SIZE / 8; i++)
	{
		err = (stack.allocate(4, (platform::U8_t**)&data));
		*data = (STACKALLOCATOR_SIZE / 4) - i;
		dataBlocks[(STACKALLOCATOR_SIZE / 8) + i] = data;
	}

	/* Assert data integrity */
	for(platform::U32_t i = 0; i < STACKALLOCATOR_SIZE / 4; i++)
	{
		if(i >= STACKALLOCATOR_SIZE / 8)
		{
			ASSERT_EQ(*dataBlocks[i], (STACKALLOCATOR_SIZE / 4) - (i - 256));
		}
		else
		{
			ASSERT_EQ(*dataBlocks[i], i);
		}
	}
}

TEST(StackAllocator, NoSpaceInStackTest)
{
	core::StackAllocator stack(STACKALLOCATOR_SIZE);
	platform::U8_t *data;
	core::StackAllocator::ErrorCode err;
	err = stack.allocate(STACKALLOCATOR_SIZE / 2, &data);
	ASSERT_EQ(err, core::StackAllocator::OK);

	err = stack.allocate(STACKALLOCATOR_SIZE, &data);
	ASSERT_EQ(err, core::StackAllocator::NOT_ENOUGH_STACK_SPACE);
}
