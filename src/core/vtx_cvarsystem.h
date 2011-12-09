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
		CVAR_FLAG_PERSISTENT	= 16,
		CVAR_FLAG_IMMUTABLE		= 32
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
		CVar(Allocator &allocator, const char *name, const char *description, const bool value, bool persistent, bool immutable);
		CVar(Allocator &allocator, const char *name, const char *description, const float value, bool persistent, bool immutable);
		CVar(Allocator &allocator, const char *name, const char *description, const char *value, bool persistent, bool immutable);
		~CVar();
		
		const char *getDescription() { return this->description; }
		const core::U32_t getFlags() { return this->flags; }
		const char *getName() { return this->name; }

		bool getBool(bool *value);
		bool getFloat(float* value);
		bool getString(const char **value);

		bool isBool() { return this->flags & CVAR_FLAG_BOOL; }
		bool isFloat() { return this->flags & CVAR_FLAG_FLOAT; }
		bool isString() { return this->flags & CVAR_FLAG_STRING; }

		bool setBool(const bool value);
		bool setFloat(const float value);
		bool setString(const char *value);
		
	};

	class CVarSystem
	{
	private:
		Allocator &alloc;
		CVar* cvarList;
		//CVarNode* insertCVar(const char *name);
	public:
		CVarSystem(Allocator &allocator);
		~CVarSystem();
		//CVarNode *getCVar(const char *name);
		CVar *getCVar(const char *name);
		CVar* insertCVar(const char *name,const char *description, const bool value, bool persistent, bool immutable);
		CVar* insertCVar(const char *name, const char *description, const float value, bool persistent, bool immutable);
		CVar* insertCVar(const char *name, const char *description, const char *value, bool persistent, bool immutable);

		// Called each frame
		void update();
	};


}

#endif