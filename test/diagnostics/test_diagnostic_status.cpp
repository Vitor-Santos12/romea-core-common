// gtest
#include <gtest/gtest.h>


// romea
#include "romea_core_common/diagnostic/Diagnostic.hpp"

//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, checkComparison)
{
  EXPECT_TRUE(romea::DiagnosticStatus::OK < romea::DiagnosticStatus::WARN);
  EXPECT_TRUE(romea::DiagnosticStatus::WARN < romea::DiagnosticStatus::ERROR);
  EXPECT_TRUE(romea::DiagnosticStatus::ERROR < romea::DiagnosticStatus::STALE);
}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, checkWorseStatus)
{
  EXPECT_EQ(worse(romea::DiagnosticStatus::OK,
                  romea::DiagnosticStatus::OK), romea::DiagnosticStatus::OK);

  EXPECT_EQ(worse(romea::DiagnosticStatus::OK,
                  romea::DiagnosticStatus::WARN), romea::DiagnosticStatus::WARN);

}

//-----------------------------------------------------------------------------
TEST(TestDiagnosticStatus, checkToStringConversion)
{
  EXPECT_STREQ(toString(romea::DiagnosticStatus::OK).c_str(), "OK");
  EXPECT_STREQ(toString(romea::DiagnosticStatus::WARN).c_str(), "WARN");
  EXPECT_STREQ(toString(romea::DiagnosticStatus::ERROR).c_str(), "ERROR");
  EXPECT_STREQ(toString(romea::DiagnosticStatus::STALE).c_str(), "STALE");

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
