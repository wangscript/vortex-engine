#include "..\..\Vortex\include\vtx_stack_allocator.h"
#include "gtest/gtest.h"

#define STACKALLOCATOR_SIZE		2048
//h

TEST(StackAllocator, AllocationTest)
{
	core::StackAllocator stack(STACKALLOCATOR_SIZE);
	U32* dataBlocks[STACKALLOCATOR_SIZE / 4];
	U32 *data;
	core::StackAllocator::ErrorCode err;
	U32 marker;
	
	/* Fill 50% of stack with integers */
	for(U32 i = 0; i < STACKALLOCATOR_SIZE / 8; i++)
	{
		err = (stack.allocate(4, (U8**)&data));
		*data = i;
		dataBlocks[i] = data;
	}

	/* Get marker */
	marker = stack.getMarker();

	/* Fill 50% of stack with integers */
	for(U32 i = 0; i < STACKALLOCATOR_SIZE / 8; i++)
	{
		err = (stack.allocate(4, (U8**)&data));
		*data = (STACKALLOCATOR_SIZE / 8) + i;
		dataBlocks[(STACKALLOCATOR_SIZE / 8) + i] = data;
	}

	/* Assert data integrity */
	for(U32 i = 0; i < STACKALLOCATOR_SIZE / 4; i++)
	{
		ASSERT_EQ(*dataBlocks[i], i);
	}

	/* Free to marker */
	stack.freeToMarker(marker);

	for(U32 i = 0; i < STACKALLOCATOR_SIZE / 8; i++)
	{
		err = (stack.allocate(4, (U8**)&data));
		*data = (STACKALLOCATOR_SIZE / 4) - i;
		dataBlocks[(STACKALLOCATOR_SIZE / 8) + i] = data;
	}

	/* Assert data integrity */
	for(U32 i = 0; i < STACKALLOCATOR_SIZE / 4; i++)
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
	U8 *data;
	core::StackAllocator::ErrorCode err;
	err = stack.allocate(STACKALLOCATOR_SIZE / 2, &data);
	ASSERT_EQ(err, core::StackAllocator::ErrorCode::OK);

	err = stack.allocate(STACKALLOCATOR_SIZE, &data);
	ASSERT_EQ(err, core::StackAllocator::ErrorCode::NOT_ENOUGH_STACK_SPACE);
}