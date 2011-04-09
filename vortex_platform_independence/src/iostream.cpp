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

#include "vtx_iostream.h"
#ifdef WIN32
#include <Windows.h>
#endif

using namespace platform;

void IOStream::init(DEVICE_HANDLE handle)
{
	this->position = 0;
	this->handle = handle;
}

U32 IOStream::getPosition()
{
	return this->position;
}

IOStream::ErrorCode IOStream::setPosition(U32 position)
{
	IOStream::ErrorCode ret;
//#ifdef WIN32
//	if(SetFilePointerEx(
//		this->handle,
//		a,
//		NULL,
//		FILE_BEGIN) != 0)
//	{
//		ret = IOStream::ErrorCode::OK;
//	}
//	else
//	{
//		// TODO: Find error codes.
//		ret = IOStream::ErrorCode::UNKOWN_ERROR;
//	}
//
//#endif

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
		ret = IOStream::ErrorCode::OK;
		position += *bytesRead;
	}
	else
	{
		ret = IOStream::ErrorCode::UNKOWN_ERROR;
	}
#endif
	return ret;
}