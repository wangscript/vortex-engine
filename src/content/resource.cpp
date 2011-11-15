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

#include <content/vtx_resource.h>
#include <core/vtx_vortex.h>
#include <io/vtx_filestream.h>

void content::ResourceManager::init()
{
}

void content::ResourceManager::destroy()
{
}

template <class T>
T content::ResourceManager::load(std::string &asset)
{
	
}

void content::ResourceManager::setPackage(const std::string &package)
{
	if(this->packageStream != NULL && this->packageStream->isOpen())
	{
		this->packageStream->closeStream();
	}

	this->packageStream->openStream(package);

	core::U32_t bytesRead;
	core::U32_t resourceCount;
	this->packageStream->readBytes(reinterpret_cast<core::U8_t*>(&resourceCount), sizeof(core::U32_t), &bytesRead);
}