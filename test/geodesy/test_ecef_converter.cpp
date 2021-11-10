// gtest
#include <gtest/gtest.h>

//romea
#include "romea_common/geodesy/ECEFConverter.hpp"

inline void checkConversions(const romea::GeodeticCoordinates & llh,
                            const Eigen::Vector3d & ecef)
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
TEST(testECEFConverter, checkConvertionAtClermont)
{
  romea::GeodeticCoordinates llh(45.78/180*M_PI,3.08/180*M_PI,365);
  Eigen::Vector3d ecef(4449694.95 ,239429.10,4548489.04);
  checkConversions(llh,ecef);
}

//-----------------------------------------------------------------------------
TEST(testECEFConverter, checkConvertionAtMelbourne)
{
  romea::GeodeticCoordinates llh(-37/180.*M_PI,144.96/180.*M_PI,10);
  Eigen::Vector3d ecef(-4175633.10 ,2928156.31, -3817399.17) ;
  checkConversions(llh,ecef);
}

//-----------------------------------------------------------------------------
TEST(testECEFConverter, checkConvertionAtAnchorage)
{
  romea::GeodeticCoordinates llh(61.17/180*M_PI,-150.02/180*M_PI,31);
  Eigen::Vector3d ecef(-2670982.26, -1540849.44, 5564529.01);
  checkConversions(llh,ecef);
}


//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
