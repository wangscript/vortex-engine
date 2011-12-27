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

#ifndef VTX_RESOURCE_H
#define VTX_RESOURCE_H

#include <core/vtx_assertions.h>
#include <content/vtx_contentpackage.h>
#include <core/vtx_allocator.h>
#include <core/vtx_atomic.h>
#include <core/vtx_vortexbase.h>
#include <core/vtx_stack_allocator.h>
#include <string>
#include <map>
#include <set>

namespace core
{
	class Blob;
	class Root;
}

namespace io
{
	class FileStream;
}

namespace content
{
	class Content;

	void InitResourceSys(core::Allocator &allocator);

	class ResourceSystem
	{
	private:
		core::Allocator &alloc;
		std::map<std::string, ContentPackage*> packageCache;
		std::map<core::U32_t, core::Blob*> blobCache;
		std::set<std::string> persistentPackages;

		template<class T1, class T2> struct can_copy {
		static void constraints(T1 a, T2 b) { T2 c = a; b = a; }
		can_copy() { void(*p)(T1,T2) = constraints; }
		};

		ContentPackage *loadPackageInternal(const std::string &path);

	public:
		enum ErrorCode { OK, NO_SUCH_PACKAGE, NO_SUCH_RESOURCE, PACKAGE_NOT_LOADED, UNKOWN_ERROR };

		ResourceSystem(core::Allocator &allocator)
			: alloc(allocator)
		{
		}
		~ResourceSystem();
		
		template <class TResource>
		ErrorCode load(std::string path, core::U32_t identifier, TResource **output)
		{
			ErrorCode result = ErrorCode::UNKOWN_ERROR;
			ASSERT(identifier >= 0);
			
#ifdef VTX_DEBUG // Only perform type-check when in debug mode.
			can_copy<TResource*, Content*>();
#endif
			core::Blob *blob = NULL;

			std::map<core::U32_t, core::Blob*>::iterator blobIterator = this->blobCache.find(identifier);

			if(blobIterator != this->blobCache.end()) // Resource exists in cache.
			{
				blob = blobIterator->second;
				ASSERT(blob != NULL);
			}
//			else // Resource does not exist in cache.
//			{
//				std::map<std::string, ContentPackage*>::iterator pkgIterator = this->packageCache.find(path);
//
//				if(pkgIterator != this->packageCache.end()) // Package exists in cache.
//				{
//					ContentPackage *package = pkgIterator->second;
//					ASSERT(package != NULL);
//					blob = package->GetContent(identifier);
//					if(blob)
//					{
//						this->blobCache[identifier] = blob;
//					}
//					else
//					{
//						result = ErrorCode::NO_SUCH_RESOURCE;
//					}
//				}
//				else // Package does not exist in cache.
//				{
//					result = ErrorCode::PACKAGE_NOT_LOADED;
//				}
//			}
//
//			if(blob)
//			{
//				TResource *resource = new (this->allocator->allocate(sizeof(TResource))) TResource(*blob, identifier);
//				resource->init(*blob);
//				*output = resource;
//				result = ErrorCode::OK;
//			}
//
			return result;
		}

		void unload(Content &content);

		void setPersistent(std::string &package);
		void setYielding(std::string &package);

		// TODO: FIX THIS!
		// If all content derives from a base class that somehow accepts a blob for initialization, the ResourceSystem could be agnostic about what type of content it is actually creating.
		//Effect *loadEffect(core::U32_t identifier);

		void loadPackage(const std::string &package);
	};

	extern ResourceSystem *resourceSys;
}

#endif
