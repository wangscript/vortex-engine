#include <core/vtx_allocator.h>
#include <text/vtx_string.h>


text::String::String(core::Allocator &allocator, const core::U8_t *string)
	: alloc(allocator)
{

	this->bufferSize = strlen(reinterpret_cast<const char*>(string)) + 1;
	this->buffer = static_cast<core::U8_t*>(this->alloc.allocate(this->bufferSize));
	memcpy(this->buffer, string, this->bufferSize);
}

text::String::String(core::Allocator &allocator, const core::U8_t *string , core::U32_t length)
	: alloc(allocator)
{
	this->bufferSize = length + 1;
	this->buffer = static_cast<core::U8_t*>(this->alloc.allocate(this->bufferSize));
	memcpy(this->buffer, string, length);
	this->buffer[length] = '\0';
	
}

text::String::~String()
{
	this->alloc.deallocate(this->buffer);
}

const core::U8_t *text::String::getU8Data()
{
	return this->buffer;
}

const char *text::String::getCharData()
{
	return reinterpret_cast<char*>(this->buffer);
}

