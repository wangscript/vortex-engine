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

#include "vtx_job.h"
#include "vtx_atomic.h"
#include "vtx_assertions.h"
#include "vtx_util.h"
#include <Windows.h>

void JobManager::init()
{
	using namespace platform;
	U32 affinity = this->getCurrentProcessAffinityMask();
	this->noJobProcessors = Utilities::getSetBitCount(affinity);
	// Can not use C++ dynamic array allocation since that requires a default parameterless constructor.
	this->processors = (JobProcessor**)malloc(sizeof(JobProcessor*) * this->noJobProcessors);
	this->initJobProcessors(affinity);
}

void JobManager::destroy()
{
	using namespace platform;
	for(U32 i = 0; i < this->noJobProcessors; i++)
	{
		delete this->processors[i];
	}
	free(this->processors);
}


void JobManager::initJobProcessors(platform::U32 processAffinity)
{
	using namespace platform;
	U32 bit = 1;
	for(int i = 0; i < this->noJobProcessors; i++)
	{
		while(!(processAffinity & bit))
			bit <<= 1;
		
		this->processors[i] = new JobProcessor(bit);
		this->processors[i]->start();
		bit <<= 1;
	}
}

platform::U32 JobManager::getCurrentProcessAffinityMask(void)
{
	using namespace platform;
	U32 processAffinity;
#ifdef WIN32
	HANDLE processHandle = GetCurrentProcess();
	U32 systemAffinity;

	BOOL success = GetProcessAffinityMask(
		processHandle,
		(PDWORD_PTR)&processAffinity,
		(PDWORD_PTR)&systemAffinity);
	ASSERT(success == true);
#endif

	return processAffinity;
}

platform::U32 JobManager::getNumberOfProcessorsAvailable(void)
{
	using namespace platform;
	U32 noProcessors;
#ifdef WIN32	
	HANDLE processHandle = GetCurrentProcess();
	U32 systemAffinity;
	U32 processAffinity;

	BOOL b = GetProcessAffinityMask(
		processHandle,
		(PDWORD_PTR)&processAffinity,
		(PDWORD_PTR)&systemAffinity);
	ASSERT(b);


	noProcessors = Utilities::getSetBitCount(processAffinity);
#endif
	return noProcessors;
}

void threadDelegate(void *data)
{
	JobProcessor *processor = (JobProcessor*)data;
	processor->process();
}

JobProcessor::JobProcessor(platform::U32 affinity)
{
	using namespace platform;
	this->affinity = affinity;
	this->thread = new Thread((ThreadFunc)threadDelegate);
	this->signal = new Signal(false);
}

void JobProcessor::start()
{
	this->thread->start(this, this->affinity);
}

void JobProcessor::process()
{
	while(true)
	{
		this->signal->waitForSignal();
		
		// Dequeue work item.

		// Process work item.

		// Discard work item.
	}
}