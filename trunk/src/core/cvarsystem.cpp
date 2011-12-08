#include <core/vtx_cvarsystem.h>
#include <core/vtx_allocator.h>
#include <string>

core::CVar::CVar(core::Allocator &allocator, const char *name, const char *description, const bool value)
	: alloc(allocator)
{
	this->name = static_cast<char*>(this->alloc.allocate(strlen(name) + 1));
	strcpy(this->name, name);

	this->description = static_cast<char*>(this->alloc.allocate(strlen(description) + 1));
	strcpy(this->description, description);


	this->value.boolValue = value;
	this->flags = CVAR_FLAG_BOOL;
}
core::CVar::CVar(core::Allocator &allocator, const char *name, const char *description, const float value)
	: alloc(allocator)
{
	this->name = static_cast<char*>(this->alloc.allocate(strlen(name) + 1));
	strcpy(this->name, name);

	this->description = static_cast<char*>(this->alloc.allocate(strlen(description) + 1));
	strcpy(this->description, description);

	this->value.floatValue = value;
	this->flags = CVAR_FLAG_FLOAT;
}

core::CVar::CVar(core::Allocator &allocator, const char *name, const char *description, const char *value)
	: alloc(allocator)
{
	this->name = static_cast<char*>(this->alloc.allocate(strlen(name) + 1));
	strcpy(this->name, name);

	this->description = static_cast<char*>(this->alloc.allocate(strlen(description) + 1));
	strcpy(this->description, description);

	this->value.stringValue = static_cast<char*>(this->alloc.allocate(strlen(value) + 1));
	strcpy(this->value.stringValue, value);
	this->flags = CVAR_FLAG_STRING;
}

core::CVar::~CVar()
{
	this->alloc.deallocate(this->name);
	this->alloc.deallocate(this->description);
	if(this->flags & CVAR_FLAG_STRING)
		this->alloc.deallocate(this->value.stringValue);
}

bool core::CVar::getBool(bool *value)
{
	if(!(this->flags & CVAR_FLAG_BOOL))
	{
		return false;
	}

	*value = this->value.boolValue;
	return true;
}

bool core::CVar::getFloat(float* value)
{
	if(!(this->flags & CVAR_FLAG_FLOAT))
	{
		return false;
	}

	*value = this->value.floatValue;
	return true;
}

bool core::CVar::getString(const char **value)
{ 
	if(!(this->flags & CVAR_FLAG_STRING))
	{
		return false;
	}
	
	*value = this->value.stringValue;
	return true;
}

bool core::CVar::setBool(const bool value)
{
	if(!(this->flags & CVAR_FLAG_BOOL))
	{
		return false;
	}

	this->value.boolValue = value;
	this->flags |= CVAR_FLAG_MODIFIED;
	return true;
}

bool core::CVar::setFloat(const float value)
{
	if(!(this->flags & CVAR_FLAG_FLOAT))
	{
		return false;
	}

	this->value.floatValue = value; 
	this->flags |= CVAR_FLAG_MODIFIED;
	return true;
}

bool core::CVar::setString(const char *value) 
{
	if(!(this->flags & CVAR_FLAG_STRING))
	{
		return false;
	}

	this->alloc.deallocate(this->value.stringValue);
	this->value.stringValue = static_cast<char*>(this->alloc.allocate(strlen(value) + 1)); 
	strcpy(this->value.stringValue, value); 
	this->flags |= CVAR_FLAG_MODIFIED;
	return true;
}

core::CVarSystem::CVarSystem(core::Allocator &allocator)
	: alloc(allocator)
{
	this->cvarList = NULL;
}

core::CVarSystem::~CVarSystem()
{
	CVar *p = this->cvarList;
	CVar *current;
	while(p)
	{
		current = p;
		p = p->next;
		
		current->~CVar();
		this->alloc.deallocate(current);
	}
}


core::CVar *core::CVarSystem::getCVar(const char *name)
{
	CVar *p = this->cvarList;

	while(p && strcmp(name, p->getName()))
	{
		p = p->next;
	}

	return p;
}
//
//core::CVarNode *core::CVarSystem::getCVar(const char *name)
//{
//	CVarNode *cvar = this->getCVarInternal(name);
//	if(!cvar)
//	{
//		cvar = this->insertCVar(name);
//	}
//
//	return cvar;
//}

//core::CVarNode *core::CVarSystem::insertCVar(const char *name)
//{
//	core::CVarNode *node = new (this->alloc.allocate(sizeof(core::CVarNode))) core::CVarNode(this->alloc, name);
//	node->next = this->cvarList;
//	this->cvarList = node;
//	return node;
//}

core::CVar* core::CVarSystem::insertCVar(const char *name, const char *description, const bool value)
{
	core::CVar *node = new (this->alloc.allocate(sizeof(core::CVar))) core::CVar(this->alloc, name, description, value);
	node->next = this->cvarList;
	this->cvarList = node;
	return node;
}

core::CVar* core::CVarSystem::insertCVar(const char *name, const char *description, const float value)
{
	core::CVar *node = new (this->alloc.allocate(sizeof(core::CVar))) core::CVar(this->alloc, name, description, value);
	node->next = this->cvarList;
	this->cvarList = node;
	return node;
}

core::CVar* core::CVarSystem::insertCVar(const char *name, const char *description, const char *value)
{
	core::CVar *node = new (this->alloc.allocate(sizeof(core::CVar))) core::CVar(this->alloc, name, description, value);
	node->next = this->cvarList;
	this->cvarList = node;
	return node;
}

void core::CVarSystem::update()
{
	CVar *p = this->cvarList;

	// Clear the modified flag for all CVars modified this frame.
	while(p)
	{
		if(p->flags & CVAR_FLAG_MODIFIED)
			p->flags &= ~CVAR_FLAG_MODIFIED;
		p = p->next;
	}
}