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

#include <concurrency/vtx_jobprocessor.h>
#include <core/vtx_atomic.h>
#include <concurrency/vtx_thread.h>
#include <concurrency/vtx_signal.h>

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