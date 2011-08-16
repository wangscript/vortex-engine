#ifndef VTX_JOBPROCESSOR_H
#define VTX_JOBPROCESSOR_H

#include <platform/vtx_atomic.h>

namespace concurrency
{
	class Signal;
	class Thread;

	class JobProcessor
	{
	public:
		explicit JobProcessor(core::U32_t affinityMask);
		void start(void);
		void process(void); // This method needs to be public for the pointer-to-member-function workaround to work.
	private:
		concurrency::Signal *signal;
		core::U32_t affinity;
		concurrency::Thread *thread;
	};

}

#endif