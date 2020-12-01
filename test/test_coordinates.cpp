// gtest
#include <gtest/gtest.h>

//romea
#include "romea_common/coordinates/PolarCoordinates.hpp"
#include "romea_common/coordinates/SphericalCoordinates.hpp"

#include <iostream>

//-----------------------------------------------------------------------------
TEST(TestCoordinates, polarToCartesianConversion)
{

  romea::CartesianCoordinates2<double> cartesianPoint(10,34.8);
  romea::PolarCoordinates<double> polarPoint = romea::toPolar(cartesianPoint);
  romea::CartesianCoordinates2<double> cartesianPoint2 = romea::toCartesian(polarPoint);

  EXPECT_NEAR(cartesianPoint.norm(),polarPoint.getRange(),0.001);
  EXPECT_NEAR(cartesianPoint.x(),cartesianPoint2.x(),0.01);
  EXPECT_NEAR(cartesianPoint.y(),cartesianPoint2.y(),0.01);

}

//-----------------------------------------------------------------------------
TEST(TestCoordinates, sphericalToCartesianConversion)
{

  romea::CartesianCoordinates3<double> cartesianPoint(-9.4,20.2,-3.4);
  romea::SphericalCoordinates<double> sphericalPoint = romea::toSpherical(cartesianPoint);
  romea::CartesianCoordinates3<double> cartesianPoint2 = romea::toCartesian(sphericalPoint);

  EXPECT_NEAR(cartesianPoint.norm(),sphericalPoint.getRange(),0.001);
  EXPECT_NEAR(cartesianPoint.x(),cartesianPoint2.x(),0.01);
  EXPECT_NEAR(cartesianPoint.y(),cartesianPoint2.y(),0.01);
  EXPECT_NEAR(cartesianPoint.z(),cartesianPoint2.z(),0.01);

}


//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
