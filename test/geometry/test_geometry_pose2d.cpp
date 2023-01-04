// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>

// romea
#include "romea_core_common/geometry/Pose2D.hpp"


//-----------------------------------------------------------------------------
TEST(TestPose2D, checkComputeEllipse)
{
  romea::Pose2D pose2d;
}


//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
