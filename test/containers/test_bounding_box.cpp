// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


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
  romea::core::AxisAlignedBoundingBox2d aabb(center, halfWidthExtents);

  EXPECT_TRUE(aabb.isInside((center + halfWidthExtents).array() - 0.1));
  EXPECT_TRUE(aabb.isInside((center - halfWidthExtents).array() + 0.1));
  EXPECT_FALSE(aabb.isInside(Eigen::Vector2d(-2.3, 4)));
  EXPECT_FALSE(aabb.isInside(Eigen::Vector2d(5.0, 2.5)));

  romea::core::Interval2D<double> interval = aabb.toInterval();
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
