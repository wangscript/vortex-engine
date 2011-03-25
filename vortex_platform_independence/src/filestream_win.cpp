#ifdef WIN32
#include "vtx_filestream.h"

void FileStream::openStream(std::string &path)
{
	// Open file for reading and writing as binary.
	this->file = CreateFileW(
					(LPCWSTR)path.c_str(),
					GENERIC_READ | GENERIC_WRITE,
					0,
					NULL,
					OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL,
					NULL);
}

void FileStream::closeStream()
{
	CloseHandle(this->file);
}

void FileStream::readBytes(U8 *buffer, U32 bufferSize)
{
	U32 bytesRead;
	ReadFile(this->file, (LPVOID)buffer, (DWORD)bufferSize, (LPDWORD)&bytesRead, NULL);
}

#endif