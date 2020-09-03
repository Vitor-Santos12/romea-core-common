// gtest
#include <gtest/gtest.h>

//romea
#include "romea_common/coordinates/CartesianCoordinates.hpp"
#include "romea_common/geodesy/ECEFConverter.hpp"
#include "romea_common/geodesy/ENUConverter.hpp"
#include "romea_common/math/EulerAngles.hpp"


inline void testECEF(const romea::GeodeticCoordinates & llh,
                     const romea::CartesianCoordinates3d & ecef)
{
  romea::ECEFConverter ecefConverter;
  Eigen::Vector3d ecefFromLLH = ecefConverter.toECEF(llh);
  romea::GeodeticCoordinates llhFromECEF = ecefConverter.toWGS84(ecefFromLLH);

  EXPECT_NEAR(llh.getLongitude(),llhFromECEF.getLongitude(),0.00000001);
  EXPECT_NEAR(llh.getLatitude(),llhFromECEF.getLatitude(),0.00000001);
  EXPECT_NEAR(llh.getAltitude(),llhFromECEF.getAltitude(),0.01);
  EXPECT_NEAR(ecef[0],ecefFromLLH[0],0.01);
  EXPECT_NEAR(ecef[1],ecefFromLLH[1],0.01);
  EXPECT_NEAR(ecef[2],ecefFromLLH[2],0.01);

}

//-----------------------------------------------------------------------------
TEST(testGeodesy, testECEFClermont)
{
  romea::GeodeticCoordinates llh(45.78/180*M_PI,3.08/180*M_PI,365);
  Eigen::Vector3d ecef(4449694.95 ,239429.10,4548489.04);
  testECEF(llh,ecef);
}

//-----------------------------------------------------------------------------
TEST(testGeodesy, testECEFMelbourne)
{
  romea::GeodeticCoordinates llh(-37/180.*M_PI,144.96/180.*M_PI,10);
  Eigen::Vector3d ecef(-4175633.10 ,2928156.31, -3817399.17) ;
  testECEF(llh,ecef);
}

//-----------------------------------------------------------------------------
TEST(testGeodesy, testECEFAnchorage)
{
  romea::GeodeticCoordinates llh(61.17/180*M_PI,-150.02/180*M_PI,31);
  Eigen::Vector3d ecef(-2670982.26, -1540849.44, 5564529.01);
  testECEF(llh,ecef);
}

//-----------------------------------------------------------------------------
inline void testENU(const romea::GeodeticCoordinates & llh,
                    const romea::CartesianCoordinates3d & enu)
{
  romea::ENUConverter enuConverter(llh);

  romea::GeodeticCoordinates llhFromENU = enuConverter.toWGS84(enu);
  Eigen::Vector3d enuFromLLH = enuConverter.toENU(llhFromENU);

  EXPECT_NEAR(enu[0],enuFromLLH[0],0.01);
  EXPECT_NEAR(enu[1],enuFromLLH[1],0.01);
  EXPECT_NEAR(enu[2],enuFromLLH[2],0.01);
}

//-----------------------------------------------------------------------------
TEST(testGeodesy, testENU)
{
  romea::GeodeticCoordinates llh(-37/180.*M_PI,144.96/180.*M_PI,10);
  testENU(llh,Eigen::Vector3d::Zero());
  testENU(llh,Eigen::Vector3d(1,-4 ,10));
  testENU(llh,Eigen::Vector3d(-0.4, 2,-7.8));
}

//-----------------------------------------------------------------------------
TEST(testGeodesy, testWGS84Distance)
{
  romea::GeodeticCoordinates llh1(45.7800/180*M_PI,3.0800/180*M_PI,365);
  romea::GeodeticCoordinates llh2(45.7801/180*M_PI,3.0801/180*M_PI,365);

  double meridionalRadius = romea::EarthEllipsoid::GRS80.meridionalRadius(llh1.getLatitude());
  double transversalRadius = romea::EarthEllipsoid::GRS80.transversalRadius(llh1.getLatitude());
  double dy= (llh2.getLatitude()-llh1.getLatitude())*meridionalRadius;
  double dx= (llh2.getLongitude()-llh1.getLongitude())*transversalRadius;

  romea::ENUConverter enuConverter1(llh1);
  Eigen::Vector3d enu2 = enuConverter1.toENU(llh2);

  EXPECT_NEAR(0,(Eigen::Vector3d(dx,dy,0)-enu2).norm(),0.01);
}

//-----------------------------------------------------------------------------
TEST(testGeodesy, testENUPrecision)
{
  romea::GeodeticCoordinates llh1(45.7800/180*M_PI,3.0800/180*M_PI,365);
  romea::GeodeticCoordinates llh2(45.7801/180*M_PI,3.0801/180*M_PI,365);
  romea::GeodeticCoordinates llh3(45.7802/180*M_PI,3.0802/180*M_PI,365);

  romea::ENUConverter enuConverter1(llh1);
  romea::ENUConverter enuConverter2(llh2);
  romea::ENUConverter enuConverter3(llh3);

  EXPECT_NEAR(0,(enuConverter2.toENU(llh1)+enuConverter2.toENU(llh3)).norm(),0.01);
  EXPECT_NEAR(0,(enuConverter1.toENU(llh2)+enuConverter1.toENU(llh3)+
                 enuConverter3.toENU(llh1)+enuConverter3.toENU(llh2)).norm(),0.01);
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
