//Copyright (C) 2011 Emil Nord�n
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

#include <vortex/vtx_clock.h>
#include <platform/vtx_timer.h>

using namespace platform;

void Clock::reset(void)
{
	this->startTime = Timer::readHighResolutionTimer();
}

F32_t Clock::getElapsedSeconds(void)
{
	U64_t now = Timer::readHighResolutionTimer();
	U64_t freq = Timer::readHighResolutionTimerFrequency();
	return ((F32_t)(now - this->startTime)) / (F32_t)freq;
}

F32_t Clock::getElapsedSecondsAndReset(void)
{
	U64_t now = Timer::readHighResolutionTimer();
	U64_t start = this->startTime;
	this->startTime = now;
	U64_t freq = Timer::readHighResolutionTimerFrequency();
	return ((F32_t)(now - start)) / (F32_t)freq;
}


