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

#include <platform/vtx_filesystem.h>
#ifdef WIN32
#include <Windows.h>
#endif


io::File::File(std::wstring *path)
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

io::File::ErrorCode io::File::exists(std::wstring *path)
{
	io::File::ErrorCode ret;
#ifdef WIN32
	WIN32_FIND_DATAW data;

	// TODO: FindFirstFile accepts wildcards in the pathname.
	// Perhaps it would be wise to make sure there are none.
	if(::FindFirstFileW(path->c_str(), &data) == INVALID_HANDLE_VALUE)
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

io::File::ErrorCode io::File::create(std::wstring *path, bool overwrite)
{
	io::File::ErrorCode ret;
#ifdef WIN32
	HANDLE handle = CreateFileW(
		path->c_str(),
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

io::File::ErrorCode io::File::deletefile(std::wstring *path)
{
	io::File::ErrorCode ret;
#if WIN32
	BOOL success = DeleteFile(path->c_str());
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

std::wstring io::File::getPath()
{
	return this->path;
}
