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

#include "vtx_renderinternal.h"
#include "vtx_atomic.h"
#include <cstring>

void RenderAPI::setClearColor(core::Vector4 &color)
{
	memcpy(this->clearColor.values, color.values, sizeof(this->clearColor.values));
}

core::Vector4 *RenderAPI::getClearColor()
{
	return &this->clearColor;
}
