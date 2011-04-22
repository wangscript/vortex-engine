#ifndef VTX_RENDERDRIVER_H
#define VTX_RENDERDRIVER_H

#include "vtx_types.h"

class RenderAPI
{
protected:
	core::Vector4 clearColor;
	RenderAPI(void) {} //Empty constructor
public:
	static RenderAPI *createDX10(void);
	virtual void swap(void) = 0;
	virtual void clear() = 0;
	void setClearColor(core::Vector4 &color);
	core::Vector4 *getClearColor();
};

#endif