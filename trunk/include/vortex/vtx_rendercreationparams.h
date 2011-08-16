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

#ifndef VTX_RENDERCREATIONPARAMS_H
#define VTX_RENDERCREATIONPARAMS_H

#include <platform/vtx_atomic.h>
#include <core/vtx_vector2.h>

namespace graphics
{

	enum E_RENDER_API
	{
		// TODO: Should all enum members be included despite an undefined directive?
		// The check could be performed in init()
		// It would provide a more stable interface, less confusion on the developer.
#ifdef VTX_COMPILE_WITH_DX10
		E_RAPI_DX10,
#endif
#ifdef VTX_COMPILE_WITH_DX11
		E_RAPI_DX11,
#endif
#ifdef VTX_COMPILE_WITH_OPENGL
		E_RAPI_OPENGL,
#endif
		E_RAPI_SOFTWARE
	};

	class RenderCreationParams
	{
	public:
		RenderCreationParams(void);
		E_RENDER_API rapi;
		core::Vector2<core::U32_t> backBufferSize;
		core::U32_t multisampleCount;
		core::U32_t multisampleQuality;
	};

}

#endif