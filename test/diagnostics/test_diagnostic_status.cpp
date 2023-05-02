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
