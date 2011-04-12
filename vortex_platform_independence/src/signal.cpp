#include "vtx_signal.h"

using namespace platform;

Signal::Signal(bool manualReset)
{
#ifdef WIN32
	this->handle = CreateEventEx(
		NULL, 
		NULL, 
		manualReset ? CREATE_EVENT_MANUAL_RESET : 0, 
		0);
#endif
}

Signal::~Signal()
{
#ifdef WIN32
	CloseHandle(this->handle);
#endif
}

void Signal::reset()
{
#ifdef WIN32
	ResetEvent(this->handle);
#endif
}

void Signal::setSignaled()
{
#ifdef WIN32
	SetEvent(this->handle);
#endif
}

void Signal::waitForSignal()
{
#ifdef WIN32
	WaitForSingleObject(this->handle, INFINITE);
#endif
}

void Signal::waitForSignal(U32 timeout)
{
#ifdef WIN32
	WaitForSingleObject(this->handle, timeout);
#endif
}