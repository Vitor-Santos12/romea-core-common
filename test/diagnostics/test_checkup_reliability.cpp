// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// gtest
#include <gtest/gtest.h>

// romea
#include "romea_core_common/diagnostic/CheckupReliability.hpp"

class TestCheckupReliability : public ::testing::Test
{
public:
  TestCheckupReliability()
  : diagnostic("foo", 0.7, 0.9)
  {
  }

  romea::CheckupReliability diagnostic;
};

//-----------------------------------------------------------------------------
TEST_F(TestCheckupReliability, compareWithLowReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.6), romea::DiagnosticStatus::ERROR);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status, romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(), "foo is too low.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(), "0.6");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupReliability, compareWithUncertainReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.75), romea::DiagnosticStatus::WARN);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status, romea::DiagnosticStatus::WARN);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(), "foo is uncertain.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(), "0.75");
}

//-----------------------------------------------------------------------------
TEST_F(TestCheckupReliability, compareWithHighReliability)
{
  EXPECT_EQ(diagnostic.evaluate(0.95), romea::DiagnosticStatus::OK);
  EXPECT_EQ(diagnostic.getReport().diagnostics.front().status, romea::DiagnosticStatus::OK);
  EXPECT_STREQ(diagnostic.getReport().diagnostics.front().message.c_str(), "foo is high.");
  EXPECT_STREQ(diagnostic.getReport().info.at("foo").c_str(), "0.95");
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
