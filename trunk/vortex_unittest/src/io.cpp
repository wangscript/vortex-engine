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
#include <io/vtx_filesystem.h>
#include <io/vtx_filestream.h>
#include <vector>

using namespace boost::intrusive;

struct delete_disposer
{
	void operator()(io::Device *delete_this)
	{  delete delete_this;  }
};

TEST(Device, GetDevices)
{
	::list<io::Device> devices;
	core::U32_t deviceCount = io::Device::getDevices(&devices);

	ASSERT_EQ(deviceCount > 0, true);

	::list<io::Device>::iterator it(devices.begin());
	::list<io::Device>::iterator itend(devices.end());
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
	io::File file(&p);
	io::File file2(&p2);
	ASSERT_EQ(file.exists(), io::File::OK);
	ASSERT_EQ(file2.exists(), io::File::FILE_DOES_NOT_EXIST);

}

TEST(File, CreateDelete)
{
	std::wstring path(L"c:\\temp\\unittest.txt");
	io::File file(&path);
	ASSERT_EQ(file.exists(), io::File::FILE_DOES_NOT_EXIST);
	ASSERT_EQ(file.create(false), io::File::OK);
	ASSERT_EQ(file.exists(), io::File::OK);
	ASSERT_EQ(file.deletefile(), io::File::OK);
	ASSERT_EQ(file.exists(), io::File::FILE_DOES_NOT_EXIST);
}

TEST(IOStream, Read)
{
	io::FileStream stream;
	stream.openStream(std::wstring(L"c:\\temp\\outfile.txt"));
	
	core::U8_t *buffer = (core::U8_t*)malloc(2);
	core::U8_t *destBuffer = (core::U8_t*)malloc(13);
	core::U32_t bytesRead;
	for(core::U32_t i = 0; i < 12; i += 2)
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
	io::FileStream stream;
	stream.openStream(std::wstring(L"c:\\temp\\outfile.txt"));

	core::U8_t *buffer = (core::U8_t*)malloc(7);
	core::U32_t bytesRead;
	ASSERT_EQ(stream.setPosition(6), io::FileStream::OK);

	ASSERT_EQ(stream.readBytes(buffer, 6, &bytesRead), io::FileStream::OK);
	buffer[6] = 0;
	ASSERT_EQ(strcmp((char*)buffer, "world!"), 0);

	stream.closeStream();
	free(buffer);
}
