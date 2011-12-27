#ifndef VTX_CONTENT
#define VTX_CONTENT

#include <core/vtx_atomic.h>
#include <core/vtx_vortexbase.h>

namespace core
{
	class Blob;
	class Root;
}

namespace content
{

	class Content
	{
		friend class ResourceSystem;
	private:
		static core::U32_t refCounter;
		core::U32_t identifier;
		core::Blob &blob;
		
	protected:
		Content(core::Blob &contentBlob, core::U32_t contentIdentifier);

		~Content();
		// I would much rather have this as a static method. But static+virtual methods does not play well.
		// ALSO, having to give each content a reference to Root is not good at all. However,
		// Some content (Effects, etc.) needs a reference to the d3ddevice, which belongs to the renderapi. How would I otherwise share this reference in a better way?
		virtual void init(core::Blob &blob) = 0;
	};
}

#endif