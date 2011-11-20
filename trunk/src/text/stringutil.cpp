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

#include <text/vtx_stringutil.h>

#include <text/utf8.h>

namespace text
{
	void StringUtil::utf8to16Vector(const std::string &in, std::vector<wchar_t> &out)
	{
		utf8::utf8to16(in.begin(), in.end(), std::back_inserter(out));
		out.push_back('\0'); // terminating null-byte.
	}
}
