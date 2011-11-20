#include <content/vtx_contentpackage.h>
#include <io/vtx_iostream.h>

namespace content
{
	ContentPackage::ContentPackage(core::Allocator &allocator, io::IOStream *packageStream)
		: alloc(allocator), stream(packageStream)
	{
		core::U32_t bytesRead;
		core::U32_t resourceCount;
		packageStream->readBytes(reinterpret_cast<core::U8_t*>(&resourceCount), sizeof(core::U32_t), &bytesRead);
		
		this->indexTable = new core::U32_t[resourceCount * 2];
		packageStream->readBytes(reinterpret_cast<core::U8_t*>(this->indexTable), resourceCount * 2 * sizeof(core::U32_t), &bytesRead);
	}
}
