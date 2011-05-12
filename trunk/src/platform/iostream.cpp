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

#include <platform/vtx_iostream.h>
#ifdef WIN32
#include <Windows.h>
#endif

using namespace platform;

IOStream::ErrorCode IOStream::init(SYSTEM_HANDLE handle)
{
	IOStream::ErrorCode ret;
	// Should not use these preprocessor #ifs here but there is something wrong with my INVALID_SYSTEM_HANDLE define.
#ifdef WIN32
	if(handle == INVALID_HANDLE_VALUE)
	{
		int err = GetLastError();
		//TODO: Find out what error codes we can expect here...
		ret = IOStream::UNKOWN_ERROR;
	}
	else
	{
		ret = IOStream::OK;
	}
#endif

	this->position = 0;
	this->handle = handle;

	return ret;
}

U64 IOStream::getPosition()
{
	return this->position;
}

IOStream::ErrorCode IOStream::setPosition(U64 position)
{
	IOStream::ErrorCode ret;
#ifdef WIN32
	LARGE_INTEGER pos;
	pos.HighPart = (position & 0xFFFFFFFF00000000) >> 32;
	pos.LowPart = (DWORD)(position & 0x00000000FFFFFFFFF);
	if(SetFilePointerEx(
		this->handle,
		pos,
		NULL,
		FILE_BEGIN) != 0)
	{
		this->position = position;
		ret = OK;
	}
	else
	{
		// TODO: Find error codes.
		int err = GetLastError();
		ret = UNKOWN_ERROR;
	}

#endif

	return ret;
}

IOStream::ErrorCode IOStream::readBytes(U8 *buffer, U32 bytesToRead, U32 *bytesRead)
{
	IOStream::ErrorCode ret;
#ifdef WIN32
	if(ReadFile(
		this->handle,
		(LPVOID)buffer,
		bytesToRead,
		(LPDWORD)bytesRead,
		NULL))
	{
		ret = IOStream::OK;
		position += *bytesRead;
	}
	else
	{
		ret = IOStream::UNKOWN_ERROR;
	}
#endif
	return ret;
}
