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

#ifndef VTX_CAMERA_H
#define VTX_CAMERA_H

namespace core
{
	class Matrix4x4;
	class Vector3;

	class Camera3D
	{
	private:
		bool viewIsDirty;
		bool projIsDirty;
	public:
		core::Vector3 *position;
		core::Vector3 *target;
		core::Vector3 *up;
		core::Matrix4x4 *view;
		core::Matrix4x4 *proj;

		Camera3D(void);
		core::Matrix4x4 *getView(void);
		core::Matrix4x4 *getProjection(void);
		void setPosition(core::Vector3 &pos);
		core::Vector3 *getPosition(void);
	};

}

#endif