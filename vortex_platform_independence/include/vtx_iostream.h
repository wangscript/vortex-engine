#ifndef VTX_IOSTREAM_H
#define VTX_IOSTREAM_H

#include "vtx_atomic.h"
#include <xstring>

class IOStream
{
public:
	typedef void (*read_callback)(U8 *buffer, U32 bytesRead);
	typedef void (*write_callback)(void);
	
	virtual void readBytes(U8 *buffer, U32 bufferSize);
	virtual void readBytes_async(U8 *buffer, U32 bufferSize, read_callback callback);
	virtual void writeBytes(U8 *buffer, U32 start, U32 length);
	virtual void writeBytes_async(U8 *buffer, U32 start, U32 length, write_callback);
	virtual void openStream(std::string path) = 0;
	virtual void closeStream();
};

#endif