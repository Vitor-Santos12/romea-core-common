// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

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

  romea::DiagnosticStatus run_checkup(const int & rate)
  {
    double dt = 1. / rate;
    romea::DiagnosticStatus status;
    for (size_t i = 0; i <= 50; ++i) {
      status = checkup.evaluate(romea::durationFromSecond(i * dt));
    }
    return status;
  }

  romea::CheckupEqualToRate checkup;
};

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, noDataReceived)
{
  EXPECT_EQ(checkup.getReport().diagnostics.front().status, romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "no data received from foo");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, rateIsOK)
{
  EXPECT_EQ(run_checkup(10), romea::DiagnosticStatus::OK);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "10");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "foo_rate is OK.");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, rateIsTooHigh)
{
  EXPECT_EQ(run_checkup(20), romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "20");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "foo_rate is too high.");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, rateIsTooLow)
{
  EXPECT_EQ(run_checkup(5), romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo_rate").c_str(), "5");
  EXPECT_STREQ(
    checkup.getReport().diagnostics.front().message.c_str(),
    "foo_rate is too low.");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, checkHeartBeatOK)
{
  EXPECT_EQ(run_checkup(10), romea::DiagnosticStatus::OK);
  EXPECT_TRUE(checkup.heartBeatCallback(romea::durationFromSecond(5)));
  EXPECT_EQ(checkup.getReport().diagnostics.front().status, romea::DiagnosticStatus::OK);
  EXPECT_EQ(checkup.getReport().diagnostics.front().message, "foo_rate is OK.");
  EXPECT_EQ(checkup.getReport().info["foo_rate"], "10");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupEqualToRate, checkHeartBeatTimeout)
{
  EXPECT_EQ(run_checkup(10), romea::DiagnosticStatus::OK);
  EXPECT_FALSE(checkup.heartBeatCallback(romea::durationFromSecond(10)));
  EXPECT_EQ(checkup.getReport().diagnostics.front().status, romea::DiagnosticStatus::STALE);
  EXPECT_EQ(checkup.getReport().diagnostics.front().message, "foo_rate timeout.");
  EXPECT_EQ(checkup.getReport().info["foo_rate"], "");
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
