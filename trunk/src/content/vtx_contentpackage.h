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
		core::U32_t resourceCount;
		core::U32_t *indexTable;
	public:
		io::IOStream *stream;

		ContentPackage(core::Allocator& allocator, io::IOStream *stream);
		~ContentPackage();
		core::Blob *GetContent(core::U32_t identifier);
	};
}

#endif
