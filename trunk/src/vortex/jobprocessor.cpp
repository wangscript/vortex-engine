#include <vortex/vtx_jobprocessor.h>
#include <platform/vtx_atomic.h>
#include <platform/vtx_thread.h>
#include <platform/vtx_signal.h>

void threadDelegate(void *data)
{
	concurrency::JobProcessor *processor = (concurrency::JobProcessor*)data;
	processor->process();
}

concurrency::JobProcessor::JobProcessor(core::U32_t affinity)
{
	this->affinity = affinity;
	this->thread = new concurrency::Thread((ThreadFunc)threadDelegate);
	this->signal = new concurrency::Signal(false);
}

void concurrency::JobProcessor::start()
{
	this->thread->start(this, this->affinity);
}

void concurrency::JobProcessor::process()
{
	while(true)
	{
		this->signal->waitForSignal();
		
		// Dequeue work item.

		// Process work item.

		// Discard work item.
	}
}