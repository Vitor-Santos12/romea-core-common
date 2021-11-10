// gtest
#include <gtest/gtest.h>

//romea
#include "romea_common/math/EulerAngles.hpp"

//-----------------------------------------------------------------------------
TEST(TestEuler, testRX)
{
  double roll=0.8;
  Eigen::Vector3d eulerAngles(roll,0,0);
  Eigen::Matrix3d R = romea::eulerAnglesToRotation3D(eulerAngles);
  eulerAngles= romea::rotation3DToEulerAngles(R);

  EXPECT_NEAR(R(0,0),1,0.001);
  EXPECT_NEAR(R(0,1),0,0.001);
  EXPECT_NEAR(R(0,2),0,0.001);
  EXPECT_NEAR(R(1,0),0,0.001);
  EXPECT_NEAR(R(2,0),0,0.001);

  EXPECT_NEAR(eulerAngles.x(),roll,0.001);
  EXPECT_NEAR(eulerAngles.y(),0,0.001);
  EXPECT_NEAR(eulerAngles.z(),0,0.001);
}

//-----------------------------------------------------------------------------
TEST(TestEuler, testRY)
{
  double pitch=M_PI_2-0.5;
  Eigen::Vector3d eulerAngles(0,pitch,0);
  Eigen::Matrix3d R = romea::eulerAnglesToRotation3D(eulerAngles);
  eulerAngles= romea::rotation3DToEulerAngles(R);

  EXPECT_NEAR(R(0,1),0,0.001);
  EXPECT_NEAR(R(1,0),0,0.001);
  EXPECT_NEAR(R(1,1),1,0.001);
  EXPECT_NEAR(R(1,2),0,0.001);
  EXPECT_NEAR(R(2,1),0,0.001);

  EXPECT_NEAR(eulerAngles.x(),0,0.001);
  EXPECT_NEAR(eulerAngles.y(),pitch,0.001);
  EXPECT_NEAR(eulerAngles.z(),0,0.001);
}


//-----------------------------------------------------------------------------
TEST(TestEuler, testRZ)
{
  double yaw=1.1;
  Eigen::Vector3d eulerAngles(0,0,yaw);
  Eigen::Matrix3d R = romea::eulerAnglesToRotation3D(eulerAngles);
  eulerAngles= romea::rotation3DToEulerAngles(R);

  EXPECT_NEAR(R(0,2),0,0.001);
  EXPECT_NEAR(R(1,2),0,0.001);
  EXPECT_NEAR(R(2,0),0,0.001);
  EXPECT_NEAR(R(2,1),0,0.001);
  EXPECT_NEAR(R(2,2),1,0.001);

  EXPECT_NEAR(eulerAngles.x(),0,0.001);
  EXPECT_NEAR(eulerAngles.y(),0,0.001);
  EXPECT_NEAR(eulerAngles.z(),yaw,0.001);

}

//-----------------------------------------------------------------------------
TEST(TestEuler, testR)
{
  double roll=0.8;
  double pitch=M_PI_2-0.5;
  double yaw=1.1;

  Eigen::Vector3d eulerAngles(roll,pitch,yaw);
  eulerAngles =romea::rotation3DToEulerAngles(romea::eulerAnglesToRotation3D(eulerAngles));
  EXPECT_NEAR(eulerAngles.x(),roll,0.001);
  EXPECT_NEAR(eulerAngles.y(),pitch,0.001);
  EXPECT_NEAR(eulerAngles.z(),yaw,0.001);
}

//-----------------------------------------------------------------------------
TEST(TestEuler, quaternionToEulerAngles)
{
  double roll=0.8;
  double pitch=-0.2;
  double yaw=2.1;
  Eigen::Vector3d eulerAngles(roll,pitch,yaw);
  Eigen::Quaterniond q=Eigen::Quaterniond(romea::eulerAnglesToRotation3D(eulerAngles));
  eulerAngles =romea::quaternionToEulerAngles(q);
  EXPECT_NEAR(eulerAngles.x(),romea::between0And2Pi(roll),0.001);
  EXPECT_NEAR(eulerAngles.y(),romea::between0And2Pi(pitch),0.001);
  EXPECT_NEAR(eulerAngles.z(),romea::between0And2Pi(yaw),0.001);
}

//-----------------------------------------------------------------------------
inline void testRotationPrediction(const Eigen::Vector3d & initialEulerAngles,
                                   const Eigen::Vector3d & angularSpeeds,
                                   const double & dt)
{
  size_t N=1000;
  Eigen::Matrix3d rotation = romea::eulerAnglesToRotation3D(initialEulerAngles);

  double dti=dt/N;
  Eigen::Matrix3d F;
  Eigen::Vector3d eulerAngles = initialEulerAngles;

  for(size_t n=0;n<N ; n++)
  {
    F.row(0)<< 1 , std::sin(eulerAngles[0])*std::tan(eulerAngles[1]),std::cos(eulerAngles[0])*std::tan(eulerAngles[1]);
    F.row(1)<< 0 , std::cos(eulerAngles[0]),-std::sin(eulerAngles[0]);
    F.row(2)<< 0 , std::sin(eulerAngles[0])/std::cos(eulerAngles[1]),std::cos(eulerAngles[0])/std::cos(eulerAngles[1]);
    eulerAngles += F*angularSpeeds*dti;

    rotation = rotation*romea::eulerAnglesToRotation3D(Eigen::Vector3d(angularSpeeds*dti));
  }

  EXPECT_LT(romea::betweenMinusPiAndPi(eulerAngles.x()-romea::rotation3DToEulerAngles(rotation).x()),0.01);
  EXPECT_LT(romea::betweenMinusPiAndPi(eulerAngles.y()-romea::rotation3DToEulerAngles(rotation).y()),0.01);
  EXPECT_LT(romea::betweenMinusPiAndPi(eulerAngles.z()-romea::rotation3DToEulerAngles(rotation).z()),0.01);
}

//-----------------------------------------------------------------------------
TEST(TestEuler, testRotationPrediction1)
{
  double dt = 1;
  Eigen::Vector3d eulerAngles(0,0,0);
  Eigen::Vector3d eulerAngularSpeed(0.3,-0.5,0.1);
  testRotationPrediction(eulerAngles,eulerAngularSpeed,dt);
}

//-----------------------------------------------------------------------------
TEST(TestEuler, testRotationPrediction2)
{

  double dt = 1;
  Eigen::Vector3d eulerAngles(0.5,-.2,.3);
  Eigen::Vector3d eulerAngularSpeed(0.3,-0.5,0.1);
  testRotationPrediction(eulerAngles,eulerAngularSpeed,dt);
}


//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
