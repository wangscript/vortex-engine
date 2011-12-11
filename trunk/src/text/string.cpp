#include <core/vtx_allocator.h>
#include <text/vtx_string.h>


text::String::String(core::Allocator &allocator, const core::U8_t *string)
	: alloc(allocator)
{
	core::U32_t stringLength = strlen(reinterpret_cast<const char*>(string)) + 1;
	this->data = static_cast<core::U8_t*>(this->alloc.allocate(stringLength));
	memcpy(this->data, string, stringLength);
}

text::String::String(core::Allocator &allocator, const core::U8_t *string , core::U32_t length)
	: alloc(allocator)
{
	this->data = static_cast<core::U8_t*>(this->alloc.allocate(length + 1));
	memcpy(this->data, string, length);
	this->data[length] = '\0';
	
}

text::String::~String()
{
	this->alloc.deallocate(this->data);
}

const core::U8_t *text::String::getU8Data()
{
	return this->data;
}

const char *text::String::getCharData()
{
	return reinterpret_cast<char*>(this->data);
}