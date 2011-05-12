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

#include <core/vtx_util.h>

platform::U8 Utilities::getSetBitCount(platform::U32 value)
{
	using namespace platform;
	U8 bitCount = 0;
	U32 currentBit = 1;
	for(U32 i = 0; i < 32; i++)
	{
		if(value & currentBit)
			bitCount++;
		currentBit <<= 1;
	}
	return bitCount;
}
