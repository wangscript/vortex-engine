//Copyright (C) 2011 Emil Nordén
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <content/vtx_ResourceSystem.h>
#include <core/vtx_vortex.h>
#include <core/vtx_standardallocator.h>
#include <io/vtx_filestream.h>
#include <content/vtx_contentpackage.h>
#include <core/vtx_blob.h>
#include <content/vtx_content.h>

content::ResourceSystem *content::resourceSys;

void content::InitResourceSys(core::Allocator &allocator)
{
	core::StandardAllocator *resourceSysAlloc = new (allocator.allocate(sizeof(core::StandardAllocator))) core::StandardAllocator;
	content::resourceSys = new (allocator.allocate(sizeof(content::ResourceSystem))) content::ResourceSystem(*resourceSysAlloc);
}

content::ResourceSystem::~ResourceSystem()
{
	for(std::map<std::string, ContentPackage*>::iterator it = this->packageCache.begin(); it != this->packageCache.end(); it++)
	{
		ContentPackage *package = it->second;
		package->~ContentPackage();
		package->stream->~IOStream();
		// The below cast is needed as to not corrupt  the heap.
		// TODO: There was a thought behind letting Content accept IOStreams, to put a layer of abstraction between Content and the type of stream it holds.
		// However, on releasing the content, I apparently MUST know the type of the stream, or the pointer will be off and the heap corrupted.
		this->alloc.deallocate(static_cast<io::FileStream*>(package->stream));
		this->alloc.deallocate(package);
	}

	for(std::map<core::U32_t, core::Blob*>::iterator it = this->blobCache.begin(); it != this->blobCache.end(); it++)
	{
		core::Blob *blob = it->second;
		this->alloc.deallocate(const_cast<void*>(blob->getPtr()));
		blob->~Blob();
		this->alloc.deallocate(blob);
	}
}

void content::ResourceSystem::unload(content::Content &content)
{
	ASSERT(content.refCounter > 0);
	content.refCounter--;
	core::Blob *blob = NULL;
	core::U32_t contentIdentifier = content.identifier;

	// The blob should be deallocated after deallocating the resource.
	// However, I must acquire a reference to the blob before deallocating the resource, or else the reference might be made useless.
	if(content.refCounter == 0)
	{
		blob = &content.blob;
	}

	content.~Content();
	this->alloc.deallocate(&content);

	if(blob)
	{
		this->blobCache.erase(contentIdentifier);
		this->alloc.deallocate(const_cast<void*>(blob->getPtr()));
		blob->~Blob();
		this->alloc.deallocate(blob);
	}

}

content::ContentPackage *content::ResourceSystem::loadPackageInternal(const std::string &path)
{
	ASSERT(this->packageCache.find(path) == this->packageCache.end());
	
	io::FileStream *packageStream = new (this->alloc.allocate(sizeof(io::FileStream))) io::FileStream;
	
	packageStream->openStream(path);
	
	ContentPackage *package = new (this->alloc.allocate(sizeof(ContentPackage))) ContentPackage(this->alloc, packageStream);
	this->packageCache[path] = package;

	return package;
}


void content::ResourceSystem::loadPackage(const std::string &path)
{
	std::map<std::string, ContentPackage*>::iterator it = this->packageCache.find(path);
	if(it == this->packageCache.end())
	{	
		io::FileStream *packageStream = new (this->alloc.allocate(sizeof(io::FileStream))) io::FileStream;

		packageStream->openStream(path);

		ContentPackage *package = new (this->alloc.allocate(sizeof(ContentPackage))) ContentPackage(this->alloc, packageStream);
		this->packageCache[path] = package;

		//core::Blob *blob = package->GetContent(3);
		//const void * ptr = blob->getPtr();
	}
}
