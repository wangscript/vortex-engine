//Copyright (c) 2011, Emil Nordén
//All rights reserved.
//
//Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef VTX_TYPES_H
#define VTX_TYPES_H

typedef unsigned int U32;
typedef signed int I32;
typedef float F32;

namespace core
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4( F32 m[4][4] );
		static void multiply(Matrix4x4 &a, Matrix4x4 &b, Matrix4x4 &result );
		__declspec(align(16)) F32 m[4][4];
	private:
	};


	class Vector2
	{
	public:
		Vector2();
		Vector2( F32 x, F32 y );
		void add( Vector2 &other, Vector2 &result );
		void subtract( Vector2 &other, Vector2 &result );
		void lerp( Vector2 &other, Vector2 &result, F32 amount );
		void multiply( Vector2 &other, Vector2 &result );
		void multiply( F32 value, Vector2 &result );
		F32 x;
		F32 y;
	private:
	};

	class Vector3
	{
	public:
		Vector3();
		Vector3( F32 x, F32 y, F32 z );
		void add( Vector3 &other, Vector3 &result );
		void subtract( Vector3 &other, Vector3 &result );
		void lerp( Vector3 &other, Vector3 &result, F32 amount );
		void multiply( Vector3 &other, Vector3 &result );
		void multiply( F32 value, Vector3 &result );
		F32 x;
		F32 y;
		F32 z;
	private:
	};

	class Vector4
	{
	public:
		Vector4();
		Vector4( F32 x, F32 y, F32 z, F32 w );
		void add( Vector4 &other, Vector4 &result );
		void subtract( Vector4 &other, Vector4 &result );
		void multiply( Vector4 &other, Vector4 &result );
		void multiply( F32 value, Vector4 &result );
		__declspec(align(16)) F32 values[4];
		//F32 x;
		//F32 y;
		//F32 z;
		//F32 w;
	private:
	};
}

#endif