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

#include "vtx_thread.h"
#include "vtx_atomic.h"
#include "vtx_signal.h"

class Job
{
public:
	typedef void (*complete_callback)(Job &job);
	Job(platform::U32 priority, complete_callback callback);
	virtual void performJob() = 0;
private:
	platform::U32 priority;
	complete_callback callback;
};

class JobProcessor
{
public:
	explicit JobProcessor(platform::U32 affinityMask);
	void start(void);
	void process(void); // This method needs to be public for the pointer-to-member-function workaround to work.
private:
	platform::Signal *signal;
	platform::U32 affinity;
	platform::Thread *thread;
};

class JobManager
{
private:
	platform::U32 promotionIncrement;
	platform::U32 noJobProcessors;
	platform::U32 getCurrentProcessAffinityMask(void);
	platform::U32 getNumberOfProcessorsAvailable(void);
	void initJobProcessors(platform::U32 processAffinity);
	JobProcessor **processors;
public:
	void init(void);
	void destroy(void);
	void setPromotionIncrement(platform::U32 value);
	platform::U32 getPromotionIncrement(void);
};

#endif