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
#include "romea_core_common/coordinates/PolarCoordinates.hpp"
#include "romea_core_common/coordinates/SphericalCoordinates.hpp"

//-----------------------------------------------------------------------------
TEST(TestCoordinates, polarToCartesianConversion)
{
  romea::CartesianCoordinates2<double> cartesianPoint(10, 34.8);
  romea::PolarCoordinates<double> polarPoint = romea::toPolar(cartesianPoint);
  romea::CartesianCoordinates2<double> cartesianPoint2 = romea::toCartesian(polarPoint);

  EXPECT_NEAR(cartesianPoint.norm(), polarPoint.getRange(), 0.001);
  EXPECT_NEAR(cartesianPoint.x(), cartesianPoint2.x(), 0.01);
  EXPECT_NEAR(cartesianPoint.y(), cartesianPoint2.y(), 0.01);
}

//-----------------------------------------------------------------------------
TEST(TestCoordinates, sphericalToCartesianConversion)
{
  romea::CartesianCoordinates3<double> cartesianPoint(-9.4, 20.2, -3.4);
  romea::SphericalCoordinates<double> sphericalPoint = romea::toSpherical(cartesianPoint);
  romea::CartesianCoordinates3<double> cartesianPoint2 = romea::toCartesian(sphericalPoint);

  EXPECT_NEAR(cartesianPoint.norm(), sphericalPoint.getRange(), 0.001);
  EXPECT_NEAR(cartesianPoint.x(), cartesianPoint2.x(), 0.01);
  EXPECT_NEAR(cartesianPoint.y(), cartesianPoint2.y(), 0.01);
  EXPECT_NEAR(cartesianPoint.z(), cartesianPoint2.z(), 0.01);
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
