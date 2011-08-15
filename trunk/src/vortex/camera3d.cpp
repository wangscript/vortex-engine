#include <vortex/vtx_camera.h>

Camera3D::Camera3D(void)
{
	this->view = new core::Matrix4x4();
}

core::Matrix4x4 *Camera3D::getView(void)
{
	if(this->viewIsDirty)
	{
		this->viewIsDirty = false;
		core::Matrix4x4::createViewMatrix(*this->position, *this->target, *this->up, *this->view);
	}
	return this->view;
}

core::Matrix4x4 *Camera3D::getProjection(void)
{
	if(this->projIsDirty)
	{
		this->projIsDirty = false;
		core::Matrix4x4::createProjection(3.14f / 2.0f, 1.666f, 0.1f, 1000.0f, *this->proj);
	}
	return this->proj;
}


void Camera3D::setPosition(core::Vector3 &pos)
{
	if(*this->position != pos)
	{
		*this->position = pos;
		this->viewIsDirty = true;
	}
}

core::Vector3 *Camera3D::getPosition(void)
{
	return this->position;
}