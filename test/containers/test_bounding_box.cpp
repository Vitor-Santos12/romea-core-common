// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>

// romea
#include "romea_core_common/containers/boundingbox/AxisAlignedBoundingBox.hpp"
#include "romea_core_common/containers/boundingbox/OrientedBoundingBox.hpp"

//-----------------------------------------------------------------------------
TEST(TestContainers, testAABB)
{
  Eigen::Vector2d center{1.5, 5.6};
  Eigen::Vector2d halfWidthExtents{3.4, 2.1};
  romea::AxisAlignedBoundingBox2d aabb(center, halfWidthExtents);

  EXPECT_TRUE(aabb.isInside((center + halfWidthExtents).array() - 0.1));
  EXPECT_TRUE(aabb.isInside((center - halfWidthExtents).array() + 0.1));
  EXPECT_FALSE(aabb.isInside(Eigen::Vector2d(-2.3, 4)));
  EXPECT_FALSE(aabb.isInside(Eigen::Vector2d(5.0, 2.5)));

  romea::Interval2D<double> interval = aabb.toInterval();
  EXPECT_DOUBLE_EQ(interval.lower()[0], center[0] - halfWidthExtents[0]);
  EXPECT_DOUBLE_EQ(interval.lower()[1], center[1] - halfWidthExtents[1]);
  EXPECT_DOUBLE_EQ(interval.upper()[0], center[0] + halfWidthExtents[0]);
  EXPECT_DOUBLE_EQ(interval.upper()[1], center[1] + halfWidthExtents[1]);
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
