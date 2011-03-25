#ifdef WIN32
#include "vtx_filesystem.h"
#include "vtx_atomic.h"
#include <Windows.h>


Device::Device()
{
}

Device::~Device()
{
	delete this->deviceName;
}

int Device::getDevices(std::vector<Device*> **devices)
{
	U32 bufferSize = 32;
	char *buffer = NULL;
	char *ptr;
	U32 length;
	do
	{
		if(buffer != NULL)
			free(buffer);
		bufferSize *= 2;
		buffer = (char*)malloc(bufferSize);
		length = ::GetLogicalDriveStringsA(bufferSize, (LPSTR)buffer);
	}while(length > bufferSize);

	U8 deviceCount = (length / 3) - 2;

	*devices = new std::vector<Device*>();

	ptr = buffer;
	for(int i = 0; i < deviceCount; i++)
	{
		Device *device = new Device();
		device->deviceName = new std::string(ptr);
		device->type = (Device::drive_type)::GetDriveTypeA((LPSTR)ptr);
		(*devices)->push_back(device);
		ptr += 4;
	}

	free(buffer);

	return deviceCount;
}
#endif