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
		Effect(void)
		{
		}

		virtual void init(core::Root &root, core::Blob &blob) = 0;
	};

}

#endif