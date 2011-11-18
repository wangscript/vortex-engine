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

#include <core/vtx_atomic.h>
#include <core/vtx_vortexbase.h>
#include <core/vtx_stack_allocator.h>
#include <string>
#include <map>

namespace core
{
	class Allocator;
	class Root;
}

namespace io
{
	class FileStream;
}

namespace content
{
	class ContentPackage;

	class ResourceManager : core::VortexBase
	{
	private:
		core::Allocator *allocator;
		std::map<std::string, ContentPackage*> packageRegistry;
		std::map<core::U32_t, void*> resourceRegistry;
	public:
		ResourceManager(core::Root& parent) : core::VortexBase(parent) {}
		void init(void);
		void destroy(void);

		template <class T>
		T load(std::string &asset);

		void loadPackage(const std::string &package);
	};

}

#endif
