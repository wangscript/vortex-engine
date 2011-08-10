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
#include <platform/vtx_atomic.h>
#ifdef WIN32
#include <Windows.h>
#endif

using namespace platform;

Device::Device()
{
}

Device::~Device()
{
	delete this->deviceName;
}

U32_t Device::getDevices(boost::intrusive::list<Device> *devices)
{
	U32_t bufferSize = 32;
	U8_t *buffer = NULL;
	U8_t *ptr;
	U32_t length;
	do
	{
		if(buffer != NULL)
			free(buffer);
		bufferSize *= 2;
		buffer = (U8_t*)malloc(bufferSize);
#ifdef WIN32
		length = ::GetLogicalDriveStringsA(bufferSize, (LPSTR)buffer);
#endif
	}while(length > bufferSize);

	U8_t deviceCount = (length / 3) - 2;

	ptr = buffer;
	for(U32_t i = 0; i < deviceCount; i++)
	{
		Device *device = new Device();
		device->deviceName = new std::string((char*)ptr);
#ifdef WIN32
		device->type = (Device::drive_type)::GetDriveTypeA((LPSTR)ptr);
#endif
		devices->push_back(*device);
		ptr += 4;
	}

	free(buffer);

	return deviceCount;
}

std::string *Device::getName()
{
	return this->deviceName;
}
