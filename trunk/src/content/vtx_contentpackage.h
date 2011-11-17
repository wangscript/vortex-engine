#ifndef VTX_CONTENTPACKAGE_H
#define VTX_CONTENTPACKAGE_H

#include <string>
#include <core/vtx_atomic.h>

namespace io
{
	class IOStream;
}

namespace content
{
	class ContentPackage
	{
	private:
		io::IOStream *stream;
		core::U32_t resourceCount;
		core::U32_t *indexTable;
	public:
		ContentPackage(io::IOStream *stream);
	};
}

#endif