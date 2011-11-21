#ifndef VTX_CONTENTPACKAGE_H
#define VTX_CONTENTPACKAGE_H

#include <string>
#include <core/vtx_atomic.h>

namespace core
{
	class Allocator;
	class Blob;
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
		core::Allocator &alloc;
		io::IOStream *stream;
		core::U32_t resourceCount;
		core::U32_t *indexTable;
	public:
		ContentPackage(core::Allocator& allocator, io::IOStream *stream);
		core::Blob *GetContent(core::U32_t identifier);
	};
}

#endif
