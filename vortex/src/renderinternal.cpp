#include "vtx_renderinternal.h"
#include "vtx_atomic.h"
#include <cstring>

void RenderAPI::setClearColor(core::Vector4 &color)
{
	memcpy_s(this->clearColor.values, sizeof(this->clearColor.values), color.values, sizeof(color.values));
}

core::Vector4 *RenderAPI::getClearColor()
{
	return &this->clearColor;
}