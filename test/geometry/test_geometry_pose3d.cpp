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
#include "romea_core_common/geometry/Pose3D.hpp"
#include "test_geometry_utils.hpp"

//-----------------------------------------------------------------------------
TEST(TestPose3D, checkConvertToPose2D)
{
  romea::core::Pose3D pose3d;
  fillEigenVector(pose3d.position, 1);
  fillEigenVector(pose3d.orientation, 4);
  fillEigenCovariance(pose3d.covariance);

  romea::core::Pose2D pose2d = romea::core::toPose2D(pose3d);

  EXPECT_DOUBLE_EQ(pose2d.yaw, pose3d.orientation.z());
  EXPECT_DOUBLE_EQ(pose2d.position.x(), pose3d.position.x());
  EXPECT_DOUBLE_EQ(pose2d.position.y(), pose3d.position.y());
  EXPECT_DOUBLE_EQ(pose2d.covariance(0, 0), pose3d.covariance(0, 0));
  EXPECT_DOUBLE_EQ(pose2d.covariance(0, 1), pose3d.covariance(0, 1));
  EXPECT_DOUBLE_EQ(pose2d.covariance(0, 2), pose3d.covariance(0, 5));
  EXPECT_DOUBLE_EQ(pose2d.covariance(1, 0), pose3d.covariance(1, 0));
  EXPECT_DOUBLE_EQ(pose2d.covariance(1, 1), pose3d.covariance(1, 1));
  EXPECT_DOUBLE_EQ(pose2d.covariance(1, 2), pose3d.covariance(1, 5));
  EXPECT_DOUBLE_EQ(pose2d.covariance(2, 0), pose3d.covariance(5, 0));
  EXPECT_DOUBLE_EQ(pose2d.covariance(2, 1), pose3d.covariance(5, 1));
  EXPECT_DOUBLE_EQ(pose2d.covariance(2, 2), pose3d.covariance(5, 5));
}

//-----------------------------------------------------------------------------
TEST(TestPose3D, checkConvertToPosition3D)
{
  romea::core::Pose3D pose3d;
  fillEigenVector(pose3d.position, 1);
  fillEigenVector(pose3d.orientation, 4);
  fillEigenCovariance(pose3d.covariance);

  romea::core::Position3D posisition3d = romea::core::toPosition3D(pose3d);
  EXPECT_DOUBLE_EQ(posisition3d.position.x(), pose3d.position.x());
  EXPECT_DOUBLE_EQ(posisition3d.position.y(), pose3d.position.y());
  EXPECT_DOUBLE_EQ(posisition3d.position.z(), pose3d.position.z());
  isSame(posisition3d.covariance, Eigen::Matrix3d(pose3d.covariance.block<3, 3>(0, 0)));
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
