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

#include "gtest/gtest.h"
#include <platform/vtx_filesystem.h>
#include <platform/vtx_filestream.h>
#include <vector>

using namespace boost::intrusive;
using namespace platform;

struct delete_disposer
{
	void operator()(Device *delete_this)
	{  delete delete_this;  }
};

TEST(Device, GetDevices)
{
	::list<Device> devices;
	U32_t deviceCount = Device::getDevices(&devices);

	ASSERT_EQ(deviceCount > 0, true);

	::list<Device>::iterator it(devices.begin());
	::list<Device>::iterator itend(devices.end());
	for(; it != itend; ++it)
	{
		// What can be asserted?
	}

	devices.clear_and_dispose(delete_disposer());
}

TEST(File, Exists)
{
	std::wstring p(L"c:\\temp\\testidag.png");
	std::wstring p2(L"c:\\temp\\thisfiledoesnotexist.txt");
	File file(&p);
	File file2(&p2);
	ASSERT_EQ(file.exists(), File::OK);
	ASSERT_EQ(file2.exists(), File::FILE_DOES_NOT_EXIST);

}

TEST(File, CreateDelete)
{
	std::wstring path(L"c:\\temp\\unittest.txt");
	File file(&path);
	ASSERT_EQ(file.exists(), File::FILE_DOES_NOT_EXIST);
	ASSERT_EQ(file.create(false), File::OK);
	ASSERT_EQ(file.exists(), File::OK);
	ASSERT_EQ(file.deletefile(), File::OK);
	ASSERT_EQ(file.exists(), File::FILE_DOES_NOT_EXIST);
}

TEST(IOStream, Read)
{
	FileStream stream;
	stream.openStream(std::wstring(L"c:\\temp\\outfile.txt"));
	
	U8_t *buffer = (U8_t*)malloc(2);
	U8_t *destBuffer = (U8_t*)malloc(13);
	U32_t bytesRead;
	for(U32_t i = 0; i < 12; i += 2)
	{
		stream.readBytes(buffer, 2, &bytesRead);
		destBuffer[i] = buffer[0];
		destBuffer[i + 1] = buffer[1];
	}
	destBuffer[12] = '\0';
	ASSERT_EQ(strcmp((char*)destBuffer, "Hello world!"), 0);

	stream.closeStream();
	free(buffer);
	free(destBuffer);	
}

TEST(IOStream, SetPosition)
{
	FileStream stream;
	stream.openStream(std::wstring(L"c:\\temp\\outfile.txt"));

	U8_t *buffer = (U8_t*)malloc(7);
	U32_t bytesRead;
	ASSERT_EQ(stream.setPosition(6), FileStream::OK);

	ASSERT_EQ(stream.readBytes(buffer, 6, &bytesRead), FileStream::OK);
	buffer[6] = 0;
	ASSERT_EQ(strcmp((char*)buffer, "world!"), 0);

	stream.closeStream();
	free(buffer);
}
