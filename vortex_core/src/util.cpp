#include "vtx_util.h"

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