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

#include "include/vtx_filesystem.h"
#ifdef WIN32
#include <Windows.h>
#endif

using namespace platform;

File::File(std::wstring *path)
{
	this->path = *path;
}

File::~File(void)
{
}

File::ErrorCode File::exists(void)
{
	return File::exists(&this->path);
}

File::ErrorCode File::exists(std::wstring *path)
{
	File::ErrorCode ret;
#ifdef WIN32
	WIN32_FIND_DATAW data;

	// TODO: FindFirstFile accepts wildcards in the pathname.
	// Perhaps it would be wise to make sure there are none.
	if(::FindFirstFileW(path->c_str(), &data) == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		if(err == ERROR_FILE_NOT_FOUND)
			ret = File::ErrorCode::FILE_DOES_NOT_EXIST;
		else
			ret = File::ErrorCode::UNKOWN_ERROR;
	}
	else
	{
		ret = File::ErrorCode::OK;
	}
	return ret;
#endif
}

File::ErrorCode File::create(bool overwrite)
{
	return File::create(&this->path, overwrite);
}

File::ErrorCode File::create(std::wstring *path, bool overwrite)
{
	File::ErrorCode ret;
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
			ret = File::ErrorCode::FILE_EXISTS;
		else
			ret = File::ErrorCode::UNKOWN_ERROR;
	}
	else
	{
		ret = File::ErrorCode::OK;
		CloseHandle(handle);
	}
#endif
	return ret;
}

File::ErrorCode File::deletefile(void)
{
	return File::deletefile(&this->path);
}

File::ErrorCode File::deletefile(std::wstring *path)
{
	File::ErrorCode ret;
#if WIN32
	BOOL success = DeleteFile(path->c_str());
	if(success)
	{
		ret = File::ErrorCode::OK;
	}
	else
	{
		DWORD err = GetLastError();
		if(err == ERROR_FILE_NOT_FOUND)
		{
			ret = File::ErrorCode::FILE_DOES_NOT_EXIST;
		}
		else
		{
			ret = File::ErrorCode::UNKOWN_ERROR;
		}
	}
#endif

	return ret;
}

std::wstring File::getPath()
{
	return this->path;
}