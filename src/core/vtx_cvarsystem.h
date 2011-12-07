#ifndef VTX_CVARSYSTEM_H
#define VTX_CVARSYSTEM_H

#include <string>
#include <core/vtx_standardallocator.h>
#include <core/vtx_atomic.h>

namespace core
{
	class Allocator;

	enum CVAR_FLAGS
	{
		CVAR_FLAG_FLOAT			= 1,
		CVAR_FLAG_STRING		= 2,
		CVAR_FLAG_BOOL			= 4,
		CVAR_FLAG_MODIFIED		= 8,
	};

	class CVar
	{
		friend class CVarSystem;
	private:
		core::Allocator &alloc;
		CVar *next;

		core::U32_t flags;
		char *name;
		char *description;
		union
		{
			float floatValue;
			char* stringValue;
			bool boolValue;
		} value;

	public:
		CVar(Allocator &allocator, const char *name, const char *description, const bool value);
		CVar(Allocator &allocator, const char *name, const char *description, const float value);
		CVar(Allocator &allocator, const char *name, const char *description, const char *value);
		~CVar();
		
		const char *getDescription() { return this->description; }
		const core::U32_t getFlags() { return this->flags; }
		const char *getName() { return this->name; }

		const bool getBool() { return this->value.boolValue; }
		const float getFloat() { return this->value.floatValue; }
		const char *getString() { return this->value.stringValue; }

		void setBool(const bool value);
		void setFloat(const float value);
		void setString(const char *value);
		
	};

	class CVarSystem
	{
	private:
		Allocator &alloc;
		CVar* cvarList;
		CVar *getCVarInternal(const char *name);
		//CVarNode* insertCVar(const char *name);
		CVar* insertCVar(const char *name, const char *description, const bool value);
		CVar* insertCVar(const char *name, const char *description, const float value);
		CVar* insertCVar(const char *name, const char *description, const char *value);
	public:
		CVarSystem(Allocator &allocator);
		~CVarSystem();
		//CVarNode *getCVar(const char *name);
		CVar *getCVar(const char *name, const char *description, const bool defaultValue);
		CVar *getCVar(const char *name, const char *description, const float defaultValue);
		CVar *getCVar(const char *name, const char *description, const char *defaultValue);

		// Called each frame
		void update();
	};


}

#endif