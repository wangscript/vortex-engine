#ifndef VTX_CONTENT
#define VTX_CONTENT

namespace core
{
	class Blob;
	class Root;
}

namespace content
{

	class Content
	{
	protected:
		Content()
		{
		}
	public:
		// I would much rather have this as a static method. But static+virtual methods does not play well.
		// ALSO, having to give each content a reference to Root is not good at all. However,
		// Some content (Effects, etc.) needs a reference to the d3ddevice, which belongs to the renderapi. How would I otherwise share this reference in a better way?
		virtual void init(core::Root &root, core::Blob &blob) = 0;
	};
}

#endif