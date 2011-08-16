#include <platform/vtx_buildconfig.h>
#include <core/vtx_util.h>
#include <core/vtx_assertions.h>
#include <platform/vtx_atomic.h>
#include <vortex/vtx_jobmanager.h>
#include <vortex/vtx_jobprocessor.h>

void concurrency::JobManager::init()
{
	core::U32_t affinity = this->getCurrentProcessAffinityMask();
	this->noJobProcessors = core::Utilities::getSetBitCount(affinity);
	// Can not use C++ dynamic array allocation since that requires a default parameterless constructor.
	this->processors = (JobProcessor**)malloc(sizeof(JobProcessor*) * this->noJobProcessors);
	this->initJobProcessors(affinity);
}

void concurrency::JobManager::destroy()
{
	for(core::U32_t i = 0; i < this->noJobProcessors; i++)
	{
		delete this->processors[i];
	}
	free(this->processors);
}


void concurrency::JobManager::initJobProcessors(core::U32_t processAffinity)
{
	core::U32_t bit = 1;
	for(core::U32_t i = 0; i < this->noJobProcessors; i++)
	{
		while(!(processAffinity & bit))
			bit <<= 1;
		
		this->processors[i] = new JobProcessor(bit);
		this->processors[i]->start();
		bit <<= 1;
	}
}
core::U32_t concurrency::JobManager::getCurrentProcessAffinityMask(void)
{
	core::U32_t processAffinity;
#if defined(VTX_PLATFORM_WIN32)
	HANDLE processHandle = GetCurrentProcess();
	core::U32_t systemAffinity;

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

core::U32_t concurrency::JobManager::getNumberOfProcessorsAvailable(void)
{
	core::U32_t noProcessors;
#if defined(VTX_PLATFORM_WIN32)
	HANDLE processHandle = GetCurrentProcess();
	core::U32_t systemAffinity;
	core::U32_t processAffinity;

	BOOL b = GetProcessAffinityMask(
		processHandle,
		(PDWORD_PTR)&processAffinity,
		(PDWORD_PTR)&systemAffinity);
	ASSERT(b);

	noProcessors = core::Utilities::getSetBitCount(processAffinity);
#elif defined(VTX_PLATFORM_LINUX)
	// TODO: Implement linux version
	noProcessors = 0;
#endif
	return noProcessors;
}

void concurrency::JobManager::setPromotionIncrement(core::U32_t value)
{
	this->promotionIncrement = value;
} 

core::U32_t concurrency::JobManager::getPromotionIncrement(void)
{
	return this->promotionIncrement;
}