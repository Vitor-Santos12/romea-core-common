// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>
#include <romea_core_common/transform/SmartRotation3D.hpp>

const double a = 60 / 180. * M_PI;
const double cosa = std::cos(60 / 180. * M_PI);
const double sina = std::sin(60 / 180. * M_PI);
const double eps = 0.0001;

//-----------------------------------------------------------------------------
TEST(testSmartRotation3D, check_roll_rotation)
{
  romea::SmartRotation3D rotation(a, 0, 0);
  EXPECT_NEAR(rotation.R()(0, 0), 1.0, eps);
  EXPECT_NEAR(rotation.R()(0, 1), 0.0, eps);
  EXPECT_NEAR(rotation.R()(0, 2), 0.0, eps);
  EXPECT_NEAR(rotation.R()(1, 0), 0.0, eps);
  EXPECT_NEAR(rotation.R()(1, 1), cosa, eps);
  EXPECT_NEAR(rotation.R()(1, 2), -sina, eps);
  EXPECT_NEAR(rotation.R()(2, 0), 0.0, eps);
  EXPECT_NEAR(rotation.R()(2, 1), sina, eps);
  EXPECT_NEAR(rotation.R()(2, 2), cosa, eps);

  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(0, 0), 1.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(0, 1), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(0, 2), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(1, 0), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(1, 1), -sina, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(1, 2), -cosa, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(2, 0), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(2, 1), cosa, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(2, 2), -sina, eps);

  Eigen::Vector3d T(1, 2, 3);
  Eigen::Vector3d RT = rotation * T;
  EXPECT_NEAR(RT(0), 1.0, eps);
  EXPECT_NEAR(RT(1), -1.5981, eps);
  EXPECT_NEAR(RT(2), 3.2321, eps);

  Eigen::Vector3d dRTdroll = rotation.dRTdAngles(T).col(0);
  EXPECT_NEAR(dRTdroll(0), 1.0000, eps);
  EXPECT_NEAR(dRTdroll(1), -3.2321, eps);
  EXPECT_NEAR(dRTdroll(2), -1.5981, eps);
}

//-----------------------------------------------------------------------------
TEST(testSmartRotation3D, check_pitch_rotation)
{
  romea::SmartRotation3D rotation(0, a, 0);
  EXPECT_NEAR(rotation.R()(0, 0), cosa, eps);
  EXPECT_NEAR(rotation.R()(0, 1), 0.0, eps);
  EXPECT_NEAR(rotation.R()(0, 2), sina, eps);
  EXPECT_NEAR(rotation.R()(1, 0), 0.0, eps);
  EXPECT_NEAR(rotation.R()(1, 1), 1.0, eps);
  EXPECT_NEAR(rotation.R()(1, 2), 0.0, eps);
  EXPECT_NEAR(rotation.R()(2, 0), -sina, eps);
  EXPECT_NEAR(rotation.R()(2, 1), 0.0, eps);
  EXPECT_NEAR(rotation.R()(2, 2), cosa, eps);

  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(0, 0), -sina, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(0, 1), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(0, 2), cosa, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(1, 0), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(1, 1), 1.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(1, 2), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(2, 0), -cosa, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(2, 1), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(2, 2), -sina, eps);

  Eigen::Vector3d T(1, 2, 3);
  Eigen::Vector3d RT = rotation * T;
  EXPECT_NEAR(RT(0), 3.0981, eps);
  EXPECT_NEAR(RT(1), 2.0, eps);
  EXPECT_NEAR(RT(2), 0.6340, eps);

  Eigen::Vector3d dRTdpitch = rotation.dRTdAngles(T).col(1);
  EXPECT_NEAR(dRTdpitch(0), 0.633975, eps);
  EXPECT_NEAR(dRTdpitch(1), 2.0, eps);
  EXPECT_NEAR(dRTdpitch(2), -3.098075, eps);
}

//-----------------------------------------------------------------------------
TEST(testSmartRotation3D, check_yaw_rotation)
{
  romea::SmartRotation3D rotation(0, 0, a);
  EXPECT_NEAR(rotation.R()(0, 0), cosa, eps);
  EXPECT_NEAR(rotation.R()(0, 1), -sina, eps);
  EXPECT_NEAR(rotation.R()(0, 2), 0.0, eps);
  EXPECT_NEAR(rotation.R()(1, 0), sina, eps);
  EXPECT_NEAR(rotation.R()(1, 1), cosa, eps);
  EXPECT_NEAR(rotation.R()(1, 2), 0.0, eps);
  EXPECT_NEAR(rotation.R()(2, 0), 0.0, eps);
  EXPECT_NEAR(rotation.R()(2, 1), 0.0, eps);
  EXPECT_NEAR(rotation.R()(2, 2), 1.0, eps);

  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(0, 0), -sina, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(0, 1), -cosa, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(0, 2), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(1, 0), cosa, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(1, 1), -sina, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(1, 2), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(2, 0), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(2, 1), 0.0, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(2, 2), 1.0, eps);

  Eigen::Vector3d T(1, 2, 3);
  Eigen::Vector3d RT = rotation * T;
  EXPECT_NEAR(RT(0), -1.2321, eps);
  EXPECT_NEAR(RT(1), 1.8660, eps);
  EXPECT_NEAR(RT(2), 3.0, eps);

  Eigen::Vector3d dRTdyaw = rotation.dRTdAngles(T).col(2);
  EXPECT_NEAR(dRTdyaw(0), -1.866025, eps);
  EXPECT_NEAR(dRTdyaw(1), -1.232050, eps);
  EXPECT_NEAR(dRTdyaw(2), 3, eps);
}

//-----------------------------------------------------------------------------
TEST(testSmartRotation3D, check_full_rotation)
{
  romea::SmartRotation3D rotation(a, a, a);
  EXPECT_NEAR(rotation.R()(0, 0), 0.250000, eps);
  EXPECT_NEAR(rotation.R()(0, 1), -0.058013, eps);
  EXPECT_NEAR(rotation.R()(0, 2), 0.966506, eps);
  EXPECT_NEAR(rotation.R()(1, 0), 0.433013, eps);
  EXPECT_NEAR(rotation.R()(1, 1), 0.899519, eps);
  EXPECT_NEAR(rotation.R()(1, 2), -0.058013, eps);
  EXPECT_NEAR(rotation.R()(2, 0), -0.866025, eps);
  EXPECT_NEAR(rotation.R()(2, 1), 0.433013, eps);
  EXPECT_NEAR(rotation.R()(2, 2), 0.250000, eps);

  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(0, 0), 0.25, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(0, 1), 0.966506, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(0, 2), 0.0580127, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(1, 0), 0.433013, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(1, 1), -0.0580127, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(1, 2), -0.899519, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(2, 0), -0.866025, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(2, 1), 0.25, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundXAxis()(2, 2), -0.433013, eps);

  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(0, 0), -0.433013, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(0, 1), -0.216506, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(0, 2), 0.875, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(1, 0), -0.75, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(1, 1), 0.625, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(1, 2), -0.216506, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(2, 0), -0.5, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(2, 1), -0.75, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundYAxis()(2, 2), -0.433013, eps);

  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(0, 0), -0.433013, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(0, 1), -0.899519, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(0, 2), 0.0580127, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(1, 0), 0.25, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(1, 1), -0.0580127, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(1, 2), 0.966506, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(2, 0), -0.866025, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(2, 1), 0.433013, eps);
  EXPECT_NEAR(rotation.dRdAngleAroundZAxis()(2, 2), 0.25, eps);

  Eigen::Vector3d T(1, 2, 3);
  Eigen::Vector3d RT = rotation * T;
  EXPECT_NEAR(RT(0), 3.0335, eps);
  EXPECT_NEAR(RT(1), 2.0580, eps);
  EXPECT_NEAR(RT(2), 0.7500, eps);

  Eigen::Matrix3d dRTdAngles = rotation.dRTdAngles(T);
  EXPECT_NEAR(dRTdAngles(0, 0), 2.35705, eps);
  EXPECT_NEAR(dRTdAngles(0, 1), 1.75897, eps);
  EXPECT_NEAR(dRTdAngles(0, 2), -2.05801, eps);
  EXPECT_NEAR(dRTdAngles(1, 0), -2.38157, eps);
  EXPECT_NEAR(dRTdAngles(1, 1), -0.149519, eps);
  EXPECT_NEAR(dRTdAngles(1, 2), 3.03349, eps);
  EXPECT_NEAR(dRTdAngles(2, 0), -1.66506, eps);
  EXPECT_NEAR(dRTdAngles(2, 1), -3.29904, eps);
  EXPECT_NEAR(dRTdAngles(2, 2), 0.75, eps);
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
