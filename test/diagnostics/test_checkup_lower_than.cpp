// gtest
#include <gtest/gtest.h>

// romea
#include "romea_core_common/diagnostic/CheckupEqualTo.hpp"


//-----------------------------------------------------------------------------
TEST(TestCheckupLowerThan, checkValueIsOK)
{
  romea::CheckupEqualTo<double> checkup("foo", 1.0, 0.1);
  EXPECT_EQ(checkup.evaluate(1.05), romea::DiagnosticStatus::OK);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(), "1.05");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(), "foo is OK.");
}

//-----------------------------------------------------------------------------
TEST(TestCheckupLowerThan, checkValueIsTooHigh)
{
  romea::CheckupEqualTo<double> checkup("foo", 1.0, 0.1);
  EXPECT_EQ(checkup.evaluate(1.15), romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(), "1.15");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(), "foo is too high.");
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
