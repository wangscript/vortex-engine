#include <content/vtx_contentpackage.h>
#include <io/vtx_iostream.h>
#include <core/vtx_allocator.h>
#include <core/vtx_blob.h>
#include <io/vtx_filestream.h>

namespace content
{
	ContentPackage::ContentPackage(core::Allocator &allocator, io::IOStream *packageStream)
		: alloc(allocator), stream(packageStream)
	{
		core::U32_t bytesRead;
		
		packageStream->readBytes(reinterpret_cast<core::U8_t*>(&this->resourceCount), sizeof(core::U32_t), &bytesRead);
		this->indexTable = reinterpret_cast<core::U32_t*>(allocator.allocate(resourceCount * 2 * sizeof(core::U32_t)));
		packageStream->readBytes(reinterpret_cast<core::U8_t*>(this->indexTable), resourceCount * 2 * sizeof(core::U32_t), &bytesRead);

	}

	ContentPackage::~ContentPackage()
	{
		this->alloc.deallocate(this->indexTable);
		if(this->stream->isOpen())
			this->stream->closeStream();
	}

	core::Blob *ContentPackage::GetContent(core::U32_t identifier)
	{
		core::Blob *contentBlob = NULL;
		core::U32_t min = 0;
		core::U32_t max = this->resourceCount;
		core::U32_t *tablePtr;
		bool found = false;

		do
		{
			core::U32_t mid = (max + min) / 2;
			tablePtr = this->indexTable + (mid * 2);

			if(*tablePtr > identifier)
			{
				max = mid - 1;
			}
			else if(*tablePtr < identifier)
			{
				min = mid + 1;
			}
			else
			{
				found = true;
			}

		}while(max >= min && !found);

		if(found)
		{
			
			this->stream->setPosition(*++tablePtr);
			core::U32_t bytesRead;
			core::U32_t contentSize;
			this->stream->readBytes(reinterpret_cast<core::U8_t*>(&contentSize), sizeof(core::U32_t), &bytesRead);
			
			void *contentData = this->alloc.allocate(contentSize);
			this->stream->readBytes(reinterpret_cast<core::U8_t*>(contentData), contentSize, &bytesRead);

			contentBlob = new (this->alloc.allocate(sizeof(core::Blob))) core::Blob(contentData, contentSize);
		}
		
		return contentBlob;
	}
}
