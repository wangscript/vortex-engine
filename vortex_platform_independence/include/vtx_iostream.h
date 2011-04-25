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

#ifndef VTX_IOSTREAM_H
#define VTX_IOSTREAM_H

#include "vtx_atomic.h"
#include <string>
#ifdef WIN32
#include <Windows.h>
#endif

namespace platform
{

	class IOStream
	{
	protected:
		SYSTEM_HANDLE handle;
		U64 position;
	public:
		enum ErrorCode { OK, UNKOWN_ERROR };
		typedef void (*read_callback)(U8 *buffer, U32 bytesRead);
		typedef void (*write_callback)(void);

		ErrorCode init(SYSTEM_HANDLE handle);
		U64 getPosition();
		ErrorCode setPosition(U64 position);
		ErrorCode readBytes(U8 *buffer, U32 bytesToRead, U32 *bytesRead);
		void readBytes_async(U8 *buffer, U32 bytesToRead, read_callback callback);
		void writeBytes(U8 *buffer, U32 start, U32 length);
		void writeBytes_async(U8 *buffer, U32 start, U32 length, write_callback);
		virtual ErrorCode openStream(std::wstring &path) = 0;
		void closeStream();
	};

}

#endif
