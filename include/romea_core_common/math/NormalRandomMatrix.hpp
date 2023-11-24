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
#include "test_utils.hpp"

//romea
#include "romea_core_mobile_base/simulation/SimulationControl2AS4WD.hpp"
#include "romea_core_mobile_base/simulation/SimulationControl4WS4WD.hpp"
#include "romea_core_mobile_base/kinematic/axle_steering/FowardOneAxleSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/axle_steering/FowardTwoAxleSteeringKinematic.hpp"
#include "romea_core_mobile_base/kinematic/wheel_steering/FowardFourWheelSteeringKinematic.hpp"

romea::core::HardwareCommand2AS4WD toHardwareCommand2AS4WD(
  const double & frontWheelRadius,
  const double & rearWheelRadius,
  const romea::core::OdometryFrame2AS4WD & odometryFrame)
{
  return {odometryFrame.frontAxleSteeringAngle,
    odometryFrame.rearAxleSteeringAngle,
    odometryFrame.frontLeftWheelLinearSpeed / frontWheelRadius,
    odometryFrame.frontRightWheelLinearSpeed / frontWheelRadius,
    odometryFrame.rearLeftWheelLinearSpeed / rearWheelRadius,
    odometryFrame.rearRightWheelLinearSpeed / rearWheelRadius};
}

romea::core::HardwareCommand4WS4WD toHardwareCommand4WS4WD(
  const double & frontWheelRadius,
  const double & rearWheelRadius,
  const romea::core::OdometryFrame4WS4WD & odometryFrame)
{
  return {odometryFrame.frontLeftWheelSteeringAngle,
    odometryFrame.frontRightWheelSteeringAngle,
    odometryFrame.rearLeftWheelSteeringAngle,
    odometryFrame.rearRightWheelSteeringAngle,
    odometryFrame.frontLeftWheelLinearSpeed / frontWheelRadius,
    odometryFrame.frontRightWheelLinearSpeed / frontWheelRadius,
    odometryFrame.rearLeftWheelLinearSpeed / rearWheelRadius,
    odometryFrame.rearRightWheelLinearSpeed / rearWheelRadius};
}

class TestSimulation2AS4WD : public ::testing::Test
{
public:
  TestSimulation2AS4WD() {}

  void SetUp()override
  {
    frontWheelRadius = 0.4;
    rearWheelRadius = 0.6;
    parameters.frontWheelBase = 0.9;
    parameters.rearWheelBase = 0.4;
    parameters.frontWheelTrack = 1.2;
    parameters.rearWheelTrack = 1.2;
    parameters.frontHubCarrierOffset = 0.1;
    parameters.rearHubCarrierOffset = 0.1;

    command.longitudinalSpeed = 1.;
    command.frontSteeringAngle = 0.6;
    command.frontSteeringAngle = -0.6;

    romea::core::OdometryFrame2AS4WD odometryCommand;
    romea::core::forwardKinematic(parameters, command, odometryCommand);
    hardwareCommand = toHardwareCommand2AS4WD(
      frontWheelRadius,
      rearWheelRadius,
      odometryCommand);

    std::cout << " hardwareCommand " << hardwareCommand << std::endl;
    simulationCommand = romea::core::toSimulationCommand2AS4WD(
      parameters.frontWheelBase +
      parameters.rearWheelBase,
      parameters.frontWheelTrack,
      parameters.rearWheelTrack,
      hardwareCommand);

    std::cout << " simulationCommand " << simulationCommand << std::endl;
  }


  double frontWheelRadius;
  double rearWheelRadius;
  romea::core::TwoAxleSteeringKinematic::Parameters parameters;

  romea::core::TwoAxleSteeringCommand command;
  romea::core::HardwareCommand2AS4WD hardwareCommand;
  romea::core::SimulationCommand2AS4WD simulationCommand;
};


TEST_F(TestSimulation2AS4WD, toSimulation)
{
  romea::core::FourWheelSteeringKinematic::Parameters parameters2;
  parameters2.frontWheelBase = parameters.frontWheelBase;
  parameters2.rearWheelBase = parameters.rearWheelBase;
  parameters2.wheelTrack = parameters.frontWheelTrack;
  parameters2.hubCarrierOffset = parameters.frontHubCarrierOffset;

  romea::core::OdometryFrame4WS4WD odometryCommand2;
  romea::core::forwardKinematic(parameters2, command, odometryCommand2);
  auto hardwareCommand2 = toHardwareCommand4WS4WD(
    frontWheelRadius,
    rearWheelRadius,
    odometryCommand2);

  EXPECT_DOUBLE_EQ(
    simulationCommand.frontAxleSteeringAngle,
    command.frontSteeringAngle);
  EXPECT_DOUBLE_EQ(
    simulationCommand.frontLeftWheelSteeringAngle,
    hardwareCommand2.frontLeftWheelSteeringAngle);
  EXPECT_DOUBLE_EQ(
    simulationCommand.frontRightWheelSteeringAngle,
    hardwareCommand2.frontRightWheelSteeringAngle);

  //    EXPECT_DOUBLE_EQ(simulationCommand.rearAxleSteeringAngle,
  //                     command.rearSteeringAngle);
  //    EXPECT_DOUBLE_EQ(simulationCommand.rearLeftWheelSteeringAngle,
  //                     hardwareCommand2.rearLeftWheelSteeringAngle);
  //    EXPECT_DOUBLE_EQ(simulationCommand.rearRightWheelSteeringAngle,
  //                     hardwareCommand2.rearRightWheelSteeringAngle);

  //    EXPECT_DOUBLE_EQ(simulationCommand.frontLeftWheelSpinningSetPoint,
  //                     hardwareCommand2.frontLeftWheelSpinningSetPoint);
  //    EXPECT_DOUBLE_EQ(simulationCommand.frontRightWheelSpinningSetPoint,
  //                     hardwareCommand2.frontRightWheelSpinningSetPoint);
  //    EXPECT_DOUBLE_EQ(simulationCommand.rearLeftWheelSpinningSetPoint,
  //                     hardwareCommand2.rearLeftWheelSpinningSetPoint);
  //    EXPECT_DOUBLE_EQ(simulationCommand.rearRightWheelSpinningSetPoint,
  //                     hardwareCommand2.rearRightWheelSpinningSetPoint);
}


TEST_F(TestSimulation2AS4WD, toHardware)
{

  //  romea::SimulationState1FASxxx simulationState;
  //  simulationState.frontAxleSteeringAngle = command.steeringAngle;
  //  simulationState.frontLeftWheelSteeringAngle = simulationCommand.frontLeftWheelSteeringAngle;
  //  simulationState.frontRightWheelSteeringAngle = simulationCommand.frontRightWheelSteeringAngle;
  //  simulationState.frontLeftWheelSpinningMotion.velocity = simulationCommand.frontLeftWheelSpinningSetPoint;
  //  simulationState.frontRightWheelSpinningMotion.velocity = simulationCommand.frontRightWheelSpinningSetPoint;
  //  simulationState.rearLeftWheelSpinningMotion.velocity = simulationCommand.rearLeftWheelSpinningSetPoint;
  //  simulationState.rearRightWheelSpinningMotion.velocity = simulationCommand.rearRightWheelSpinningSetPoint;

  //  auto hardwareState =romea::toHardwareState1FAS2FWD(parameters.rearWheelBase+
  //                                                     parameters.frontWheelBase,
  //                                                     parameters.frontWheelTrack,
  //                                                     simulationState);

  //  EXPECT_DOUBLE_EQ(hardwareState.frontAxleSteeringAngle,
  //                   hardwareCommand.frontAxleSteeringAngle);
  //  EXPECT_DOUBLE_EQ(hardwareState.frontLeftWheelSpinningMotion.velocity,
  //                   hardwareCommand.frontLeftWheelSpinningSetPoint);
  //  EXPECT_DOUBLE_EQ(hardwareState.frontRightWheelSpinningMotion.velocity,
  //                   hardwareCommand.frontRightWheelSpinningSetPoint);

}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
