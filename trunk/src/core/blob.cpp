#include <core/vtx_blob.h>

core::Blob::Blob(const void *pointer, core::U64_t dataSize)
{
	this->ptr = pointer;
	this->size = dataSize;
}

const void *core::Blob::getPtr()
{
	return this->ptr;
}

core::U64_t core::Blob::getSize()
{
	return this->size;
}