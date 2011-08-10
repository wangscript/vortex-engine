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

#include <platform/vtx_defineconfig.h>
#include <vortex/vtx_job.h>
#include <platform/vtx_atomic.h>
#include <core/vtx_assertions.h>
#include <core/vtx_util.h>
#include <stdlib.h>
#if defined(VTX_PLATFORM_WIN32)
#include <Windows.h>
#endif

using namespace platform;

void JobManager::init()
{
	U32_t affinity = this->getCurrentProcessAffinityMask();
	this->noJobProcessors = Utilities::getSetBitCount(affinity);
	// Can not use C++ dynamic array allocation since that requires a default parameterless constructor.
	this->processors = (JobProcessor**)malloc(sizeof(JobProcessor*) * this->noJobProcessors);
	this->initJobProcessors(affinity);
}

void JobManager::destroy()
{
	for(U32_t i = 0; i < this->noJobProcessors; i++)
	{
		delete this->processors[i];
	}
	free(this->processors);
}


void JobManager::initJobProcessors(U32_t processAffinity)
{
	U32_t bit = 1;
	for(U32_t i = 0; i < this->noJobProcessors; i++)
	{
		while(!(processAffinity & bit))
			bit <<= 1;
		
		this->processors[i] = new JobProcessor(bit);
		this->processors[i]->start();
		bit <<= 1;
	}
}
U32_t JobManager::getCurrentProcessAffinityMask(void)
{
	U32_t processAffinity;
#if defined(VTX_PLATFORM_WIN32)
	HANDLE processHandle = GetCurrentProcess();
	U32_t systemAffinity;

	BOOL success = GetProcessAffinityMask(
		processHandle,
		(PDWORD_PTR)&processAffinity,
		(PDWORD_PTR)&systemAffinity);
	ASSERT(success == TRUE);
#elif defined(VTX_PLATFORM_LINUX)
	// TODO: Find process affinity here.
	processAffinity = 0;
#endif

	return processAffinity;
}

U32_t JobManager::getNumberOfProcessorsAvailable(void)
{
	U32_t noProcessors;
#if defined(VTX_PLATFORM_WIN32)
	HANDLE processHandle = GetCurrentProcess();
	U32_t systemAffinity;
	U32_t processAffinity;

	BOOL b = GetProcessAffinityMask(
		processHandle,
		(PDWORD_PTR)&processAffinity,
		(PDWORD_PTR)&systemAffinity);
	ASSERT(b);

	noProcessors = Utilities::getSetBitCount(processAffinity);
#elif defined(VTX_PLATFORM_LINUX)
	// TODO: Implement linux version
	noProcessors = 0;
#endif
	return noProcessors;
}

void JobManager::setPromotionIncrement(U32_t value)
{
	this->promotionIncrement = value;
} 

platform::U32_t JobManager::getPromotionIncrement(void)
{
	return this->promotionIncrement;
}

void threadDelegate(void *data)
{
	JobProcessor *processor = (JobProcessor*)data;
	processor->process();
}

JobProcessor::JobProcessor(platform::U32_t affinity)
{
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

Job::Job(U32_t priority, complete_callback callback)
{
	this->priority = priority;
	this->callback = callback;
}
