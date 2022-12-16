// gtest
#include <gtest/gtest.h>

// romea
#include "romea_core_common/geodesy/ENUConverter.hpp"

//-----------------------------------------------------------------------------
inline void checkConversions(const romea::GeodeticCoordinates & llh,
                             const Eigen::Vector3d & enu)
{
  romea::ENUConverter enuConverter(llh);

  romea::GeodeticCoordinates llhFromENU = enuConverter.toWGS84(enu);
  Eigen::Vector3d enuFromLLH = enuConverter.toENU(llhFromENU);

  EXPECT_NEAR(enu[0], enuFromLLH[0], 0.01);
  EXPECT_NEAR(enu[1], enuFromLLH[1], 0.01);
  EXPECT_NEAR(enu[2], enuFromLLH[2], 0.01);
}

//-----------------------------------------------------------------------------
TEST(testENUConverter, checkConversions)
{
  auto llh = romea::makeGeodeticCoordinates(-37/180.*M_PI, 144.96/180.*M_PI, 10);
  checkConversions(llh, Eigen::Vector3d::Zero());
  checkConversions(llh, Eigen::Vector3d(1, -4 , 10));
  checkConversions(llh, Eigen::Vector3d(-0.4, 2, -7.8));
}

//-----------------------------------------------------------------------------
TEST(testENUConverter, checkConversionPrecision)
{
  auto llh1 = romea::makeGeodeticCoordinates(45.7800/180*M_PI, 3.0800/180*M_PI, 365);
  auto llh2 = romea::makeGeodeticCoordinates(45.7801/180*M_PI, 3.0801/180*M_PI, 365);
  auto llh3 = romea::makeGeodeticCoordinates(45.7802/180*M_PI, 3.0802/180*M_PI, 365);

  romea::ENUConverter enuConverter1(llh1);
  romea::ENUConverter enuConverter2(llh2);
  romea::ENUConverter enuConverter3(llh3);

  EXPECT_NEAR(0, (enuConverter2.toENU(llh1)+enuConverter2.toENU(llh3)).norm(), 0.01);
  EXPECT_NEAR(0, (enuConverter1.toENU(llh2)+enuConverter1.toENU(llh3)+
                  enuConverter3.toENU(llh1)+enuConverter3.toENU(llh2)).norm(), 0.01);
}

////-----------------------------------------------------------------------------
// TEST(testGeodesy, testWGS84Distance)
//{
//  romea::GeodeticCoordinates llh1(45.7800/180*M_PI,3.0800/180*M_PI,365);
//  romea::GeodeticCoordinates llh2(45.7801/180*M_PI,3.0801/180*M_PI,365);

//  double meridionalRadius = romea::EarthEllipsoid::GRS80.meridionalRadius(llh1.getLatitude());
//  double transversalRadius = romea::EarthEllipsoid::GRS80.transversalRadius(llh1.getLatitude());
//  double dy= (llh2.getLatitude()-llh1.getLatitude())*meridionalRadius;
//  double dx= (llh2.getLongitude()-llh1.getLongitude())*transversalRadius;

//  romea::ENUConverter enuConverter1(llh1);
//  Eigen::Vector3d enu2 = enuConverter1.toENU(llh2);

//  EXPECT_NEAR(0,(Eigen::Vector3d(dx,dy,0)-enu2).norm(),0.01);
//}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
