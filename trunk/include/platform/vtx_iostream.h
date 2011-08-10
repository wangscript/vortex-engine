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

#include <platform/vtx_atomic.h>
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
		U64_t position;
	public:
		enum ErrorCode { OK, UNKOWN_ERROR };
		typedef void (*read_callback)(U8_t *buffer, U32_t bytesRead);
		typedef void (*write_callback)(void);

		ErrorCode init(SYSTEM_HANDLE handle);
		U64_t getPosition();
		ErrorCode setPosition(U64_t position);
		ErrorCode readBytes(U8_t *buffer, U32_t bytesToRead, U32_t *bytesRead);
		void readBytes_async(U8_t *buffer, U32_t bytesToRead, read_callback callback);
		void writeBytes(U8_t *buffer, U32_t start, U32_t length);
		void writeBytes_async(U8_t *buffer, U32_t start, U32_t length, write_callback);
		virtual ErrorCode openStream(std::wstring &path) = 0;
		void closeStream();
	};

}

#endif
