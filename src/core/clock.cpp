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

#include <core/vtx_clock.h>
#include <core/vtx_timer.h>

void core::Clock::reset(void)
{
	this->startTime = core::Timer::readHighResolutionTimer();
}

core::F32_t core::Clock::getElapsedSeconds(void)
{
	core::U64_t now = core::Timer::readHighResolutionTimer();
	core::U64_t freq = core::Timer::readHighResolutionTimerFrequency();
	return ((core::F32_t)(now - this->startTime)) / (core::F32_t)freq;
}

core::F32_t core::Clock::getElapsedSecondsAndReset(void)
{
	core::U64_t now = core::Timer::readHighResolutionTimer();
	core::U64_t start = this->startTime;
	this->startTime = now;
	core::U64_t freq = core::Timer::readHighResolutionTimerFrequency();
	return ((core::F32_t)(now - start)) / (core::F32_t)freq;
}


