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

#include <platform/vtx_signal.h>

concurrency::Signal::Signal(bool manualReset)
{
#ifdef WIN32
	this->handle = CreateEventEx(
		NULL, 
		NULL, 
		manualReset ? CREATE_EVENT_MANUAL_RESET : 0, 
		0);
#endif
}

concurrency::Signal::~Signal()
{
#ifdef WIN32
	CloseHandle(this->handle);
#endif
}

void concurrency::Signal::reset()
{
#ifdef WIN32
	ResetEvent(this->handle);
#endif
}

void concurrency::Signal::setSignaled()
{
#ifdef WIN32
	SetEvent(this->handle);
#endif
}

void concurrency::Signal::waitForSignal()
{
#ifdef WIN32
	WaitForSingleObject(this->handle, INFINITE);
#endif
}

void concurrency::Signal::waitForSignal(core::U32_t timeout)
{
#ifdef WIN32
	WaitForSingleObject(this->handle, timeout);
#endif
}
