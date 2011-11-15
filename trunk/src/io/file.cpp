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

#include <io/vtx_filesystem.h>
#ifdef WIN32
#include <Windows.h>
#include <text\vtx_stringutil.h>
#endif


io::File::File(std::string *path)
{
	this->path = *path;
}

io::File::~File(void)
{
}

io::File::ErrorCode io::File::exists(void)
{
	return io::File::exists(&this->path);
}

io::File::ErrorCode io::File::exists(std::string *path)
{
	io::File::ErrorCode ret;
#ifdef WIN32
	WIN32_FIND_DATAW data;

	std::vector<wchar_t> widePath;
	text::StringUtil::utf8to16Vector(*path, widePath);

	// TODO: FindFirstFile accepts wildcards in the pathname.
	// Perhaps it would be wise to make sure there are none.
	if(::FindFirstFileW(&widePath.front(), &data) == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		if(err == ERROR_FILE_NOT_FOUND)
			ret = File::FILE_DOES_NOT_EXIST;
		else
			ret = File::UNKOWN_ERROR;
	}
	else
	{
		ret = File::OK;
	}
	return ret;
#endif
}

io::File::ErrorCode io::File::create(bool overwrite)
{
	return io::File::create(&this->path, overwrite);
}

io::File::ErrorCode io::File::create(std::string *path, bool overwrite)
{
	io::File::ErrorCode ret;
#ifdef WIN32

	std::vector<wchar_t> widePath;
	text::StringUtil::utf8to16Vector(*path, widePath);

	HANDLE handle = CreateFileW(
		&widePath.front(),
		0, // Dont access the file after creation.
		0, // Dont allow other processes to access the file until we've closed the handle.
		NULL,
		overwrite ? CREATE_ALWAYS : CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(handle == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		// TODO: What error codes does CreateFileW return?
		if(err == ERROR_FILE_EXISTS)
			ret = io::File::FILE_EXISTS;
		else
			ret = io::File::UNKOWN_ERROR;
	}
	else
	{
		ret = io::File::OK;
		CloseHandle(handle);
	}
#endif
	return ret;
}

io::File::ErrorCode io::File::deletefile(void)
{
	return io::File::deletefile(&this->path);
}

io::File::ErrorCode io::File::deletefile(std::string *path)
{
	io::File::ErrorCode ret;
#if WIN32
	
	std::vector<wchar_t> widePath;
	text::StringUtil::utf8to16Vector(*path, widePath);

	BOOL success = DeleteFile(&widePath.front());
	if(success)
	{
		ret = io::File::OK;
	}
	else
	{
		DWORD err = GetLastError();
		if(err == ERROR_FILE_NOT_FOUND)
		{
			ret = File::FILE_DOES_NOT_EXIST;
		}
		else
		{
			ret = File::UNKOWN_ERROR;
		}
	}
#endif

	return ret;
}

std::string io::File::getPath()
{
	return this->path;
}
