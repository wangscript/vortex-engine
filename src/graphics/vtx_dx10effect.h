#ifndef VTX_DX10EFFECT_H
#define VTX_DX10EFFECT_H

#include <core/vtx_buildconfig.h>

#if defined(VTX_PLATFORM_WIN32) && defined(VTX_COMPILE_WITH_DX10)

#include <graphics/vtx_effect.h>
#include <D3D10effect.h>

namespace core
{
	class Blob;
	class Root;
}

namespace graphics
{
	class DX10Effect : public Effect
	{
	public:
		ID3D10Effect &d3dEffect;
		DX10Effect(ID3D10Effect &effect, core::Blob &blob, core::U32_t effectIdentifier) : Effect(blob, effectIdentifier),
			d3dEffect(effect)
		{
		}

		virtual void init(core::Blob &blob);
	};
}

#endif

#endif