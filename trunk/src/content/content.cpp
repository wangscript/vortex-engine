#include <content/vtx_content.h>
#include <core/vtx_atomic.h>
#include <core/vtx_vortex.h>
#include <core/vtx_blob.h>

core::U32_t content::Content::refCounter;

content::Content::Content(core::Blob &contentBlob, core::U32_t contentIdentifier) 
	: blob(contentBlob), identifier(contentIdentifier)
{
	refCounter++;
}

content::Content::~Content()
{
}