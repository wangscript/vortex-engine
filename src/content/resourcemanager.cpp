//Copyright (C) 2011 Emil Nord�n
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

#include <content/vtx_resourcemanager.h>
#include <core/vtx_vortex.h>
#include <core/vtx_standardallocator.h>
#include <io/vtx_filestream.h>
#include <content/vtx_contentpackage.h>
#include <core/vtx_blob.h>

void content::ResourceManager::init()
{
	this->allocator = new core::StandardAllocator();
}

void content::ResourceManager::destroy()
{
	delete this->allocator;
}

template <class TResource>
TResource content::ResourceManager::load(core::U32_t identifier)
{
	typedef typename TResource::value_type T;

}

void content::ResourceManager::loadPackage(const std::string &path)
{
	std::map<std::string, ContentPackage*>::iterator it = this->packageRegistry.find(path);
	if(it == this->packageRegistry.end())
	{	
		io::FileStream *packageStream = new (this->allocator->allocate(sizeof(io::FileStream))) io::FileStream;

		packageStream->openStream(path);

		ContentPackage *package = new (this->allocator->allocate(sizeof(ContentPackage))) ContentPackage(*this->allocator, packageStream);
		this->packageRegistry[path] = package;

		core::Blob *blob = package->GetContent(3);
		const void * ptr = blob->getPtr();
	}
}