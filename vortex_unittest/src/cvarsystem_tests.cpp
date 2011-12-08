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

	// Run test in a more narrow scope, so that the CVarSystem instance is automatically disposed before we assert for no memory leaks.
	{
		core::CVarSystem system(allocator);
		float value;
		bool result;
		core::CVar *cvar;
		cvar = system.getCVar("c_Test");
		EXPECT_TRUE(cvar == NULL);
		
		cvar = system.insertCVar("c_Test", "This is a test", 3.14f);
		ASSERT_TRUE(cvar != NULL);
		EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_FLOAT);
		
		result = cvar->getFloat(&value);

		ASSERT_TRUE(result);
		EXPECT_EQ(value, 3.14f);
		
		result = cvar->setFloat(2.0f);

		ASSERT_TRUE(result);

		result = cvar->getFloat(&value);

		ASSERT_TRUE(result);
		EXPECT_EQ(value, 2.0f);
	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}

TEST(CVarSystem, MultipleInsertAndRetrieval)
{
	core::StandardAllocator allocator;

	// Run test in a more narrow scope, so that the CVarSystem instance is automatically disposed before we assert for no memory leaks.
	{
		core::CVarSystem system(allocator);
		const char *text;
		bool boolValue;
		bool result;
		core::CVar *cvar, *cvar2, *cvar3;

		cvar = system.getCVar("c_Test");
		EXPECT_TRUE(cvar == NULL);
		
		cvar = system.insertCVar("c_Test", "This is a test", 3.14f);
		ASSERT_TRUE(cvar != NULL);
		EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_FLOAT);

		float value;
		result = cvar->getFloat(&value);
		ASSERT_TRUE(result);
		EXPECT_EQ(value, 3.14f);

		cvar2 = system.getCVar("c_Test");
		EXPECT_EQ(cvar, cvar2);

		system.insertCVar("c_1", "Description #1", true);
		system.insertCVar("c_2", "Description #2", false);
		system.insertCVar("c_3", "Description #3", "Foo");

		cvar = system.getCVar("c_1");
		cvar2 = system.getCVar("c_2");
		cvar3 = system.getCVar("c_3");

		EXPECT_STREQ(cvar->getName(), "c_1");
		EXPECT_STREQ(cvar->getDescription(), "Description #1");
		EXPECT_EQ(cvar->getFlags(), core::CVAR_FLAG_BOOL);

		result = cvar->getBool(&boolValue);
		
		ASSERT_TRUE(result);
		EXPECT_EQ(boolValue, true);

		EXPECT_STREQ(cvar2->getName(), "c_2");
		EXPECT_STREQ(cvar2->getDescription(), "Description #2");
		EXPECT_EQ(cvar2->getFlags(), core::CVAR_FLAG_BOOL);

		result = cvar2->getBool(&boolValue);

		ASSERT_TRUE(result);
		EXPECT_EQ(boolValue, false);

		EXPECT_STREQ(cvar3->getName(), "c_3");
		EXPECT_STREQ(cvar3->getDescription(), "Description #3");
		EXPECT_EQ(cvar3->getFlags(), core::CVAR_FLAG_STRING);
		result = cvar3->getString(&text);
		ASSERT_TRUE(result);
		EXPECT_STREQ(text, "Foo");		
	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}

TEST(CVarSystem, ModifyCVar)
{
	core::StandardAllocator allocator;
	// Run test in a more narrow scope, so that the CVarSystem instance is automatically disposed before we assert for no memory leaks.
	{
		core::CVarSystem system(allocator);
		const char *text;
		bool result;

		core::CVar *cvar = system.insertCVar("MyCVar", "Im new here!", "Foo");
		ASSERT_TRUE(cvar != NULL);

		result = cvar->getString(&text);

		ASSERT_STREQ(text, "Foo");
		EXPECT_STREQ(text, "Foo");
		EXPECT_FALSE(cvar->getFlags() & core::CVAR_FLAG_MODIFIED);

		result = cvar->setString("Bar");

		ASSERT_TRUE(result);

		result = cvar->getString(&text);

		ASSERT_TRUE(result);
		EXPECT_STREQ(text, "Bar");
		EXPECT_TRUE(cvar->getFlags() & core::CVAR_FLAG_MODIFIED);

	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}

TEST(CVarSystem, CVarInvalidSetCall)
{
	core::StandardAllocator allocator;
	// Run test in a more narrow scope, so that the CVarSystem instance is automatically disposed before we assert for no memory leaks.
	{
		core::CVarSystem system(allocator);

		core::CVar *cvar = system.insertCVar("MyCVar", "I cant find my cat!", 123.5f);

		ASSERT_TRUE(cvar->isFloat());
		ASSERT_FALSE(cvar->isString());
		ASSERT_FALSE(cvar->isBool());

		ASSERT_FALSE(cvar->setString("Foo"));

		ASSERT_FALSE(cvar->isString());

		float value;
		ASSERT_TRUE(cvar->getFloat(&value));
		ASSERT_EQ(value, 123.5f);
	}
	ASSERT_EQ(allocator.allocatedSize(), 0.0f);
}