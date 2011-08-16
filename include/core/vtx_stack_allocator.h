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


#ifndef VTX_STACK_ALLOCATOR_H
#define VTX_STACK_ALLOCATOR_H

#include <platform/vtx_atomic.h>

namespace core
{
	class StackAllocator
	{
	private:
		core::U32_t stackSize;
		core::U8_t *data;
		core::U32_t stackPosition;
	public:
		enum ErrorCode{	OK,	NOT_ENOUGH_STACK_SPACE };
		StackAllocator( core::U32_t stackSize );
		~StackAllocator();	
		ErrorCode allocate( core::U32_t size , core::U8_t **allocatedSpace );
		void freeToMarker( core::U32_t stackPosition );
		core::U32_t getMarker();
	};
}

#endif
