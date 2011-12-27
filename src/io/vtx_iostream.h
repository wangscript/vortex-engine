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

#include <core/vtx_atomic.h>
#include <string>
#ifdef WIN32
#include <Windows.h>
#endif

namespace io
{

	class IOStream
	{
	protected:
		core::SYSTEM_HANDLE handle;
		core::U64_t position;
		bool open;
	public:
		enum ErrorCode { OK, UNKOWN_ERROR, END_OF_FILE };
		typedef void (*read_callback)(core::U8_t *buffer, core::U32_t bytesRead);
		typedef void (*write_callback)(void);

		ErrorCode init(core::SYSTEM_HANDLE handle);
		core::U64_t getPosition();
		ErrorCode readByte(core::U8_t *byte);
		ErrorCode readBytes(core::U8_t *buffer, core::U32_t bytesToRead, core::U32_t *bytesRead);
		void readBytes_async(core::U8_t *buffer, core::U32_t bytesToRead, read_callback callback);
		ErrorCode setPosition(core::U64_t position);
		void writeBytes(core::U8_t *buffer, core::U32_t start, core::U32_t length);
		void writeBytes_async(core::U8_t *buffer, core::U32_t start, core::U32_t length, write_callback);
		void closeStream();
		bool isOpen();
	};

}

#endif
