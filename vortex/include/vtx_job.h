#ifndef VTX_JOB_H
#define VTX_JOB_H

#include "vtx_thread.h"
#include "vtx_atomic.h"
#include "vtx_signal.h"

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
	platform::U32 noJobProcessors;
	platform::U32 getCurrentProcessAffinityMask(void);
	platform::U32 getNumberOfProcessorsAvailable(void);
	void initJobProcessors(platform::U32 processAffinity);
	JobProcessor **processors;
public:
	void init(void);
	void destroy(void);
};

#endif