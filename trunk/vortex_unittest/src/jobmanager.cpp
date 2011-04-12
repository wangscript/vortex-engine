#include "gtest/gtest.h"
#include "vtx_job.h"

TEST(JobManager, Init)
{
	JobManager manager;
	manager.init();
}