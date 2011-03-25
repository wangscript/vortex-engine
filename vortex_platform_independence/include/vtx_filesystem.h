#ifndef VTX_FILESYSTEM_H
#define VTX_FILESYSTEM_H

#include <vector>

class Device
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

	static Device empty;

	~Device();
	static int getDevices(std::vector<Device*> **devices);
	drive_type getDriveType();
	std::string getString();
private:
	drive_type type;
	std::string *deviceName;
	Device();
};

#endif