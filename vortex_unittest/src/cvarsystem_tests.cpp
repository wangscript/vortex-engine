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

	// Run test in a tighter scope, so that the CVarSystem instance is automatically disposed in the end.
	{
		core::CVarSystem system(allocator);
		
		core::CVar *cvar;
		cvar = system.getCVar("c_Test");
		EXPECT_TRUE(cvar == NULL);
		
		cvar = system.insertCVar("c_Test", "This is a test", 3.14f);
		ASSERT_TRUE(cvar != NULL);
		EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_FLOAT);
		
		EXPECT_EQ(cvar->getFloat(), 3.14f);
		
		cvar->setFloat(2.0f);
		
		EXPECT_EQ(cvar->getFloat(), 2.0f);
	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}

TEST(CVarSystem, MultipleInsertAndRetrieval)
{
	core::StandardAllocator allocator;

	// Run test in a tighter scope, so that the CVarSystem instance is automatically disposed in the end.
	{
		core::CVarSystem system(allocator);
		core::CVar *cvar, *cvar2, *cvar3;
		cvar = system.getCVar("c_Test");
		EXPECT_TRUE(cvar == NULL);
		
		cvar = system.insertCVar("c_Test", "This is a test", 3.14f);
		ASSERT_TRUE(cvar != NULL);
		EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_FLOAT);
		EXPECT_EQ(cvar->getFloat(), 3.14f);

		cvar2 = system.getCVar("c_Test");
		EXPECT_EQ(cvar, cvar2);

		system.insertCVar("c_1", "Description #1", true);
		system.insertCVar("c_2", "Description #2", false);
		system.insertCVar("c_3", "Description #3", "Foo");

		cvar = system.getCVar("c_1");
		cvar2 = system.getCVar("c_2");
		cvar3 = system.getCVar("c_3");

		EXPECT_EQ(cvar->getName(), "c_1");
		EXPECT_EQ(cvar->getDescription(), "Description #1");
		EXPECT_EQ(cvar->getFlags(), core::CVAR_FLAG_BOOL);
		EXPECT_EQ(cvar->getBool(), true);

		EXPECT_EQ(cvar2->getName(), "c_2");
		EXPECT_EQ(cvar2->getDescription(), "Description #2");
		EXPECT_EQ(cvar2->getFlags(), core::CVAR_FLAG_BOOL);
		EXPECT_EQ(cvar2->getBool(), false);

		EXPECT_EQ(cvar3->getName(), "c_3");
		EXPECT_EQ(cvar3->getDescription(), "Description #3");
		EXPECT_EQ(cvar3->getFlags(), core::CVAR_FLAG_STRING);
		EXPECT_EQ(cvar3->getString(), "Foo");		
	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}

TEST(CVarSystem, ModifyCVar)
{
	core::StandardAllocator allocator;
	// Run test in a tighter scope, so that the CVarSystem instance is automatically disposed in the end.
	{
		core::CVarSystem system(allocator);

		core::CVar *cvar = system.insertCVar("MyCVar", "Im new here!", "Foo");
		ASSERT_TRUE(cvar != NULL);
		EXPECT_EQ(cvar->getString(), "Foo");
		EXPECT_FALSE(cvar->getFlags() & core::CVAR_FLAG_MODIFIED);

		cvar->setString("Bar");

		EXPECT_EQ(cvar->getString(), "Bar");
		EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_MODIFIED);

	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}