// gtest
#include <gtest/gtest.h>

//romea
#include "romea_core_common/diagnostic/CheckupEqualTo.hpp"


//-----------------------------------------------------------------------------
TEST(TestCheckupGreaterThan, checkValueIsOK)
{
  romea::CheckupEqualTo<double> checkup("foo", 1.0, 0.1);
  EXPECT_EQ(checkup.evaluate(0.95), romea::DiagnosticStatus::OK);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(), "0.95");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(), "foo is OK.");
}

//-----------------------------------------------------------------------------
TEST(TestCheckupGreaterThan, checkValueIsTooLow)
{
  romea::CheckupEqualTo<double> checkup("foo", 1.0, 0.1);
  EXPECT_EQ(checkup.evaluate(0.85), romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(), "0.85");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(), "foo is too low.");
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
