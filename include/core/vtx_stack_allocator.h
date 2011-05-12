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

#include <core/vtx_types.h>

//
namespace core
{
	class StackAllocator
	{
	private:
		platform::U32 stackSize;
		platform::U8 *data;
		platform::U32 stackPosition;
	public:
		enum ErrorCode{	OK,	NOT_ENOUGH_STACK_SPACE };
		StackAllocator( platform::U32 stackSize );
		~StackAllocator();	
		ErrorCode allocate( platform::U32 size , platform::U8 **allocatedSpace );
		void freeToMarker( platform::U32 stackPosition );
		platform::U32 getMarker();
	};
}

#endif
