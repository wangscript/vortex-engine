//Copyright (c) 2011, Emil Nordén
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "..\include\vtx_types.h"

using namespace core;

Vector4::Vector4( F32 x, F32 y, F32 z, F32 w )
{
	this->values[0] = x;
	this->values[1] = y;
	this->values[2] = z;
	this->values[3] = w;
	//this->x = x;
	//this->y = y;
	//this->z = z;
	//this->w = w;
}

void Vector4::add( Vector4 &other, Vector4 &result )
{
	//result.x = this->x + other.x;
	//result.y = this->y + other.y;
	//result.z = this->z + other.z;
	//result.w = this->w + other.w;
}

void Vector4::subtract( Vector4 &other, Vector4 &result )
{
	//result.x = this->x - other.x;
	//result.y = this->y - other.y;
	//result.z = this->z - other.z;
	//result.w = this->w - other.w;
}

void Vector4::multiply( Vector4 &other, Vector4 &result )
{
	//result.x = this->x * other.x;
	//result.y = this->y * other.y;
	//result.z = this->z * other.z;
	//result.w = this->w * other.w;
}

void Vector4::multiply( F32 value, Vector4 &result )
{
	//result.x = this->x * value;
	//result.y = this->y * value;
	//result.z = this->z * value;
	//result.w = this->w * value;
}