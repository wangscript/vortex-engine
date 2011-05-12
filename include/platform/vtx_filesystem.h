//Copyright (C) 2011 Emil Nord�n
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

#ifndef VTX_FILESYSTEM_H
#define VTX_FILESYSTEM_H

#include <platform/vtx_atomic.h>
#include <boost/intrusive/list.hpp>
#include <vector>

namespace platform
{

	class Device
		: public boost::intrusive::list_base_hook<>
	{
	public:
		enum drive_type
		{
			unknown,
			invalid,
			removable,
			fixed,
			network,
			disc,
			ramdisk
		};
		~Device();
		static U32 getDevices(boost::intrusive::list<Device> *devices);
		drive_type getDriveType();
		std::string *getName();
		Device();
	private:
		drive_type type;
		std::string *deviceName;

	};

	class File
	{
	private:
		std::wstring path;
	public:
		File(std::wstring *path);
		~File(void);
		enum ErrorCode { OK, FILE_DOES_NOT_EXIST, UNAUTHORIZED, FILE_EXISTS, UNKOWN_ERROR };
		//TODO: Rewrite these IO functions. It should really return a bool, but how to remove need for errorcode?
		static ErrorCode create(std::wstring *path, bool overwrite);
		static ErrorCode deletefile(std::wstring *path);
		static ErrorCode exists(std::wstring *path);
		ErrorCode create(bool overwrite);
		ErrorCode deletefile(void);
		ErrorCode exists(void);
		std::wstring getPath();
	};

	class Directory
	{
	};

}

#endif