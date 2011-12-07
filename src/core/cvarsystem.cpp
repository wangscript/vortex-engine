#include <core/vtx_cvarsystem.h>
#include <core/vtx_allocator.h>
#include <string>

core::CVar::CVar(core::Allocator &allocator, const char *name, const char *description, const bool value)
	: alloc(allocator)
{
	this->name = static_cast<char*>(this->alloc.allocate(strlen(name)));
	strcpy(this->name, name);

	this->description = static_cast<char*>(this->alloc.allocate(strlen(description)));
	strcpy(this->description, description);


	this->value.boolValue = value;
	this->flags = CVAR_FLAG_BOOL;
}
core::CVar::CVar(core::Allocator &allocator, const char *name, const char *description, const float value)
	: alloc(allocator)
{
	this->name = static_cast<char*>(this->alloc.allocate(strlen(name)));
	strcpy(this->name, name);

	this->description = static_cast<char*>(this->alloc.allocate(strlen(description)));
	strcpy(this->description, description);

	this->value.floatValue = value;
	this->flags = CVAR_FLAG_BOOL;
}

core::CVar::CVar(core::Allocator &allocator, const char *name, const char *description, const char *value)
	: alloc(allocator)
{
	this->name = static_cast<char*>(this->alloc.allocate(strlen(name)));
	strcpy(this->name, name);

	this->description = static_cast<char*>(this->alloc.allocate(strlen(description)));
	strcpy(this->description, description);

	this->value.stringValue = static_cast<char*>(this->alloc.allocate(strlen(value)));
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

void core::CVar::setBool(const bool value)
{
	this->value.boolValue = value;
	this->flags |= CVAR_FLAG_MODIFIED;
}

void core::CVar::setFloat(const float value)
{
	this->value.floatValue = value; 
	this->flags |= CVAR_FLAG_MODIFIED;
}

void core::CVar::setString(const char *value) 
{
	this->alloc.deallocate(this->value.stringValue);
	this->value.stringValue = static_cast<char*>(this->alloc.allocate(strlen(value))); 
	strcpy(this->value.stringValue, this->value.stringValue); 
	this->flags |= CVAR_FLAG_MODIFIED;
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


core::CVar *core::CVarSystem::getCVarInternal(const char *name)
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

core::CVar *core::CVarSystem::getCVar(const char *name, const char *defaultDescription, const bool defaultValue)
{
	CVar *cvar = this->getCVarInternal(name);
	if(!cvar)
	{
		cvar = this->insertCVar(name, defaultDescription, defaultValue);
	}

	return cvar;
}
core::CVar *core::CVarSystem::getCVar(const char *name, const char *defaultDescription, const float defaultValue)
{
	CVar *cvar = this->getCVarInternal(name);
	if(!cvar)
	{
		cvar = this->insertCVar(name, defaultDescription, defaultValue);
	}

	return cvar;
}
core::CVar *core::CVarSystem::getCVar(const char *name, const char *defaultDescription, const char *defaultValue)
{
	CVar *cvar = this->getCVarInternal(name);
	if(!cvar)
	{
		cvar = this->insertCVar(name, defaultDescription, defaultValue);
	}

	return cvar;
}

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