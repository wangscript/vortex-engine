#ifndef VTX_FILESTREAM_H
#define VTX_FILESTREAM_H

#include "vtx_iostream.h"
#ifdef WIN32
	#include <Windows.h>
#endif

class FileStream : IOStream
{
public:
	void readBytes(U8 *buffer, U32 bufferSize);
	void readBytesAsync(U8 *buffer, U32 bufferSize, read_callback callback);
	void writeBytes(U8 *buffer, U32 start, U32 length);
	void writeBytesAsync(U8 *buffer, U32 start, U32 length, write_callback);
	void openStream(std::string &path);
	void closeStream();
private:
#ifdef WIN32
	HANDLE file;
#endif
};

#endif