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

#include <vortex/vtx_camera.h>
#include <core/vtx_matrix4x4.h>
#include <core/vtx_vector3.h>

core::Camera3D::Camera3D(void)
{
	this->view = new core::Matrix4x4();
}

core::Matrix4x4 *core::Camera3D::getView(void)
{
	if(this->viewIsDirty)
	{
		this->viewIsDirty = false;
		core::Matrix4x4::createViewMatrix(*this->position, *this->target, *this->up, *this->view);
	}
	return this->view;
}

core::Matrix4x4 *core::Camera3D::getProjection(void)
{
	if(this->projIsDirty)
	{
		this->projIsDirty = false;
		core::Matrix4x4::createProjection(3.14f / 2.0f, 1.666f, 0.1f, 1000.0f, *this->proj);
	}
	return this->proj;
}


void core::Camera3D::setPosition(core::Vector3 &pos)
{
	if(*this->position != pos)
	{
		*this->position = pos;
		this->viewIsDirty = true;
	}
}

core::Vector3 *core::Camera3D::getPosition(void)
{
	return this->position;
}