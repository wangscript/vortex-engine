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

#include <graphics/vtx_rendercreationparams.h>

#define DEFAULT_BACKBUFFER_WIDTH	800
#define DEFAULT_BACKBUFFER_HEIGHT	600

graphics::RenderCreationParams::RenderCreationParams(void)
{
	this->backBufferSize.x = DEFAULT_BACKBUFFER_WIDTH;
	this->backBufferSize.y = DEFAULT_BACKBUFFER_HEIGHT;
	this->multisampleCount = 1;
	this->multisampleQuality = 0;
	this->rapi = E_RAPI_SOFTWARE; // Software rendering by default.
}
