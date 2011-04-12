#ifndef VTX_SIGNAL_H
#define VTX_SIGNAL_H

#include "vtx_atomic.h"

namespace platform
{

	class Signal
	{
	private:
		SYSTEM_HANDLE handle;
	public:
		explicit Signal(bool manualReset);
		~Signal();
		void setSignaled();
		void reset();
		void waitForSignal(void);
		void waitForSignal(U32 timeout);
	};

}

#endif