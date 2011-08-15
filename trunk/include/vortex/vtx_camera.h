#ifndef VTX_CAMERA_H
#define VTX_CAMERA_H

#include <core/vtx_types.h>

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

#endif