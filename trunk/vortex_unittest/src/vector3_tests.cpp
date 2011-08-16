#include "gtest/gtest.h"
#include <core/vtx_vector3.h>

TEST(Vector3, Normalize)
{
	core::Vector3 v(45.6f, 1.0f, 32.31f);
	v.normalize();
	ASSERT_EQ(v.x, 0.81582642f);
	ASSERT_EQ(v.y, 0.017890930f);
	ASSERT_EQ(v.z, 0.57805598f);

}