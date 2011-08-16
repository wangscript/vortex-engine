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

#ifndef VTX_RENDERMANAGER_H
#define VTX_RENDERMANAGER_H

#include <vortex/vtx_vortexbase.h>

// Forward declarations
namespace graphics
{
	class RenderCreationParams;
	class RenderAPI;
}

namespace core
{
	class WindowCreationParams;
	class NativeWindow;
}

namespace graphics
{

	class RenderManager : core::VortexBase
	{
	public:
		RenderManager(core::Root&);
		void init(graphics::RenderCreationParams &params, core::WindowCreationParams &windowParams);
		void destroy(void);
		graphics::RenderAPI *getRenderObject(void);
	private:
		void createWindow(core::WindowCreationParams &params);
		core::NativeWindow *window;
		bool manageWindow;
		graphics::RenderAPI *render;
	};

}

#endif
