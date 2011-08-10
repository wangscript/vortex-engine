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

#ifndef VTX_JOB_H
#define VTX_JOB_H

//#include <vortex/vtx_vortexbase.h>
#include <platform/vtx_thread.h>
#include <platform/vtx_atomic.h>
#include <platform/vtx_signal.h>

class Job
{
public:
	typedef void (*complete_callback)(Job &job);
	Job(platform::U32_t priority, complete_callback callback);
	virtual void performJob() = 0;
private:
	platform::U32_t priority;
	complete_callback callback;
};

class JobProcessor
{
public:
	explicit JobProcessor(platform::U32_t affinityMask);
	void start(void);
	void process(void); // This method needs to be public for the pointer-to-member-function workaround to work.
private:
	platform::Signal *signal;
	platform::U32_t affinity;
	platform::Thread *thread;
};

class JobManager
{
private:
	platform::U32_t promotionIncrement;
	platform::U32_t noJobProcessors;
	platform::U32_t getCurrentProcessAffinityMask(void);
	platform::U32_t getNumberOfProcessorsAvailable(void);
	void initJobProcessors(platform::U32_t processAffinity);
	JobProcessor **processors;
public:
	void init(void);
	void destroy(void);
	void setPromotionIncrement(platform::U32_t value);
	platform::U32_t getPromotionIncrement(void);
};

#endif
