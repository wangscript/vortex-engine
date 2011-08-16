#ifndef VTX_JOBMANAGER_H
#define VTX_JOBMANAGER_H

#include <platform/vtx_atomic.h>

namespace concurrency
{
	class JobProcessor;

	class JobManager
	{
	private:
		core::U32_t promotionIncrement;
		core::U32_t noJobProcessors;
		core::U32_t getCurrentProcessAffinityMask(void);
		core::U32_t getNumberOfProcessorsAvailable(void);
		void initJobProcessors(core::U32_t processAffinity);
		JobProcessor **processors;
	public:
		void init(void);
		void destroy(void);
		void setPromotionIncrement(core::U32_t value);
		core::U32_t getPromotionIncrement(void);
	};

}

#endif