// gtest
#include <gtest/gtest.h>

//romea
#include "romea_core_common/diagnostic/CheckupEqualTo.hpp"


//-----------------------------------------------------------------------------
TEST(TestCheckupEqualTo, checkValueIsToHigh)
{
  romea::CheckupEqualTo<double> checkup("foo",1.0,0.1);
  EXPECT_EQ(checkup.evaluate(1.2),romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(),"1.2");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(),"foo is too high.");
}

//-----------------------------------------------------------------------------
TEST(TestCheckupEqualTo, checkValueIsOK)
{
  romea::CheckupEqualTo<double> checkup("foo",1.0,0.1);
  EXPECT_EQ(checkup.evaluate(1.05),romea::DiagnosticStatus::OK);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(),"1.05");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(),"foo is OK.");
}

//-----------------------------------------------------------------------------
TEST(TestCheckupEqualTo, checkValueIsTooLow)
{
  romea::CheckupEqualTo<double> checkup("foo",1.0,0.1);
  EXPECT_EQ(checkup.evaluate(0.8),romea::DiagnosticStatus::ERROR);
  EXPECT_STREQ(checkup.getReport().info.at("foo").c_str(),"0.8");
  EXPECT_STREQ(checkup.getReport().diagnostics.front().message.c_str(),"foo is too low.");

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
