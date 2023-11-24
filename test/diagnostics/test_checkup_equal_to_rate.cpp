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
#include "romea_core_common/diagnostic/CheckupRate.hpp"

//-----------------------------------------------------------------------------
class TestCheckupEqualToRate : public ::testing::Test
{
public:
  TestCheckupEqualToRate()
  : checkup("foo", 10, 0.1)
  {
  }

  romea::core::DiagnosticStatus run_checkup(const int & rate)
  {
    double dt = 1. / rate;
    romea::core::DiagnosticStatus status;
    for (size_t i = 0; i <= 50; ++i) {
      status = checkup.evaluate(romea::core::durationFromSecond(i * dt));
    }
    return status;
  }

  romea::core::CheckupEqualToRate checkup;
};

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, noDataReceived)
{
  EXPECT_EQ(checkup.getReport().diagnostics.front().status, romea::core::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "no data received from foo");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, rateIsOK)
{
  EXPECT_EQ(run_checkup(10), romea::core::DiagnosticStatus::OK);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "10");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "foo_rate is OK.");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, rateIsTooHigh)
{
  EXPECT_EQ(run_checkup(20), romea::core::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "20");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "foo_rate is too high.");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, rateIsTooLow)
{
  EXPECT_EQ(run_checkup(5), romea::core::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "5");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "foo_rate is too low.");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, checkHeartBeatOK)
{
  EXPECT_EQ(run_checkup(10), romea::core::DiagnosticStatus::OK);
  EXPECT_TRUE(checkup.heartBeatCallback(romea::core::durationFromSecond(5)));
  EXPECT_EQ(checkup.getReport().diagnostics.front().status, romea::core::DiagnosticStatus::OK);
  EXPECT_EQ(checkup.getReport().diagnostics.front().message, "foo_rate is OK.");
  EXPECT_EQ(checkup.getReport().info["foo_rate"], "10");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, checkHeartBeatTimeout)
{
  EXPECT_EQ(run_checkup(10), romea::core::DiagnosticStatus::OK);
  EXPECT_FALSE(checkup.heartBeatCallback(romea::core::durationFromSecond(10)));
  EXPECT_EQ(checkup.getReport().diagnostics.front().status, romea::core::DiagnosticStatus::STALE);
  EXPECT_EQ(checkup.getReport().diagnostics.front().message, "foo_rate timeout.");
  EXPECT_EQ(checkup.getReport().info["foo_rate"], "");
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
