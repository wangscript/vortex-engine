//Copyright (C) 2011 Emil Nordén
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef VTX_EVENTOUTPUT_H
#define VTX_EVENTOUTPUT_H

#include <core/vtx_atomic.h>

#include <string>
#include <iostream>
#include <map>

namespace core
{

	class EventOutput
	{
	public:
		enum E_LEVEL { E_LEVEL_VERBOSE, E_LEVEL_INFO, E_LEVEL_WARNING, E_LEVEL_ERROR, E_LEVEL_FATAL };
		std::map<E_LEVEL, std::string> map;
		EventOutput( E_LEVEL level) : reportLevel(level), outStream(&std::cerr) {};
		EventOutput( E_LEVEL level, std::ostream* out) : reportLevel(level), outStream(out) {};  
		void reportEvent( E_LEVEL, std::string& );
		void reportEvent( E_LEVEL, char* );
		void reportMethodFailedEvent( E_LEVEL, std::string&, core::U32_t );
		void setOutputLevel( E_LEVEL );
		void setOutput( std::ostream* );
	private:
		E_LEVEL reportLevel;
		std::ostream *outStream;
		void initMap(void);
		void outputToStream( E_LEVEL, std::string& );
	};

}

#endif