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

#include <core/vtx_buildconfig.h>
#include <io/vtx_filestream.h>
#include <text/vtx_stringutil.h>

io::FileStream::~FileStream()
{
	this->closeStream();
}

io::IOStream::ErrorCode io::FileStream::openStream(const std::string &path)
{
	// Open file for reading and writing as binary.
	core::SYSTEM_HANDLE handle;
	// TODO: Fix unix variant!
#ifdef WIN32

	std::vector<wchar_t> widePath;
	text::StringUtil::utf8to16Vector(path, widePath);

	handle = CreateFileW(
		&widePath.front(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
#endif
	return this->init(handle);
}