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

#include <core/vtx_eventoutput.h>
#include <platform/vtx_atomic.h>
#include <core/vtx_assertions.h>
#include <sstream>

void core::EventOutput::reportEvent( E_LEVEL level, std::wstring& message )
{
	ASSERT(level >= 0 && level <= E_LEVEL_FATAL);
	if(this->reportLevel <= level)
	{
		this->outputToStream(level, message);
		//*this->outStream << L": " << message << std::endl;
	}
}

void core::EventOutput::reportEvent( E_LEVEL level, wchar_t* message)
{
	ASSERT(level >= 0 && level <= E_LEVEL_FATAL);
	if(this->reportLevel <= level)
	{
		std::wstring msg(message);
		this->outputToStream(level, msg);
	}
}

void core::EventOutput::reportMethodFailedEvent( E_LEVEL level, std::wstring& method, core::U32_t errorCode)
{
	ASSERT(level >= 0 && level <= E_LEVEL_FATAL);
	if(this->reportLevel <= level)
	{
		std::wstringstream strstream;
		strstream << "Method '"	 << method << "' failed (" << errorCode << ")" << std::endl;
		std::wstring msg(strstream.str());
		this->outputToStream(level, msg);
	}
}

void core::EventOutput::outputToStream( E_LEVEL level, std::wstring& message )
{
	*this->outStream << L": " << message << std::endl;
}

void core::EventOutput::setOutputLevel( E_LEVEL level )
{
	this->reportLevel = level;
}

void core::EventOutput::setOutput( std::wostream *out )
{
	if(!out)
		this->outStream = &std::wcerr;
	else
		this->outStream = out;
}
