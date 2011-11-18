#ifndef VTX_CONTENTPACKAGE_H
#define VTX_CONTENTPACKAGE_H

#include <string>
#include <core/vtx_atomic.h>

namespace core
{
	class Allocator;
}

namespace io
{
	class IOStream;
}

namespace content
{
	class ContentPackage
	{
	private:
		Allocator &alloc;
		io::IOStream *stream;
		core::U32_t resourceCount;
		core::U32_t *indexTable;
	public:
		ContentPackage(Allocator& alloc, io::IOStream *stream);
	};
}

#endif