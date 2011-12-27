#ifndef VTX_EFFECT_H
#define VTX_EFFECT_H

#include <content/vtx_content.h>

namespace core
{
	class Blob;
	class Root;
}

namespace graphics
{
	class RenderAPI;
}

namespace graphics
{

	class Effect : public content::Content
	{
	public:
		Effect(core::Blob &effectBlob, core::U32_t effectIdentifier) : content::Content(effectBlob, effectIdentifier)
		{
		}

		void init(core::Blob &blob);
	};

}

#endif