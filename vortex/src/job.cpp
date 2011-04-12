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