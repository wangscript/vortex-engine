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

#include <core/vtx_cvarsystem.h>
#include <core/vtx_standardallocator.h>
#include "gtest/gtest.h"

TEST(CVarSystem, SingleInsertAndRetrieval)
{
	core::StandardAllocator allocator;

	core::CVarSystem system(allocator);

	core::CVarNode *cvar, *cvar2;
	cvar = system.getCVar("c_Test", "Test Cvar #1", 3.14f);
	EXPECT_TRUE(cvar != NULL);

	EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_FLOAT);

	EXPECT_EQ(cvar->getFloat(), 3.14f);
	
	cvar->setFloat(2.0f);

	EXPECT_EQ(cvar->getFloat(), 2.0f);
}

TEST(CVarSystem, MultipleInsertAndRetrieval)
{
	core::StandardAllocator allocator;

	core::CVarSystem system(allocator);

	core::CVarNode *cvar, *cvar2;

	// Get first CVar
	cvar = system.getCVar("c_Test", "Test CVar #1",  "Foo");
	ASSERT_TRUE(cvar != NULL);

	// Assert name and description of CVar.
	EXPECT_STRCASEEQ(cvar->getName(), "c_Test");
	EXPECT_STRCASEEQ(cvar->getDescription(), "Test CVar #1");

	// Get second CVar
	cvar2 = system.getCVar("c_Test2", "Test CVar #2", "Bar");
	ASSERT_TRUE(cvar2 != NULL);
	ASSERT_NE(cvar, cvar2);

	// -- Assert data integrity of first CVar
	EXPECT_STRCASEEQ(cvar->getName(), "c_Test");
	EXPECT_STRCASEEQ(cvar->getDescription(), "Test CVar #1");
	
	// Assert name and description of CVar
	ASSERT_STRCASEEQ(cvar2->getName(), "c_Test2");
	ASSERT_STRCASEEQ(cvar2->getDescription(), "Test CVar #2");

	// Get first CVar again, this time there will be no insertion in the internal linked list.
	cvar2 = system.getCVar("c_Test", "", "Test");
	EXPECT_TRUE(cvar2 != NULL);
	ASSERT_EQ(cvar, cvar2);
	
	// Assert data integrity of first CVar
	// No data should have been altered since there was no insertion in the last command
	// Altough this wouldnt be a thourough test if I didnt assume that **** can happen! :)
	EXPECT_STRCASEEQ(cvar2->getName(), "c_Test");
	EXPECT_STRCASEEQ(cvar2->getDescription(), "Test CVar #1");


}