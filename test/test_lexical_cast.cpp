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
#include "romea_core_common/lexical/LexicalCast.hpp"


//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToDouble)
{
  EXPECT_DOUBLE_EQ(romea::lexical_cast<double>("10.4"), 10.4);
  EXPECT_DOUBLE_EQ(romea::lexical_cast<double>("8"), 8);
  EXPECT_DOUBLE_EQ(romea::lexical_cast<double>("1.8e2"), 180);
  EXPECT_THROW(romea::lexical_cast<double>("string"), std::invalid_argument);
}

//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToFloat)
{
  EXPECT_FLOAT_EQ(romea::lexical_cast<float>("-10.23"), -10.23);
  EXPECT_FLOAT_EQ(romea::lexical_cast<float>("2"), 2);
  EXPECT_DOUBLE_EQ(romea::lexical_cast<double>("12e-2"), 0.12);
  EXPECT_THROW(romea::lexical_cast<float>("string"), std::invalid_argument);
}


//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToInt)
{
  EXPECT_EQ(romea::lexical_cast<int>("10"), 10);
  EXPECT_EQ(romea::lexical_cast<int>("-2"), -2);
  // EXPECT_EQ(romea::lexical_cast<int>("2e2"),-200);
  EXPECT_THROW(romea::lexical_cast<int>("10000000000"), std::out_of_range);
  EXPECT_THROW(romea::lexical_cast<int>("3.14"), std::invalid_argument);
  EXPECT_THROW(romea::lexical_cast<int>("string"), std::invalid_argument);
}

//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToLong)
{
  EXPECT_EQ(romea::lexical_cast<long>("10"), 10);
  EXPECT_EQ(romea::lexical_cast<long>("-2"), -2);
  EXPECT_THROW(romea::lexical_cast<long>("10000000000000000000"), std::out_of_range);
}

//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToLongDouble)
{
  EXPECT_DOUBLE_EQ(romea::lexical_cast<long double>("10.45"), 10.45);
  EXPECT_DOUBLE_EQ(romea::lexical_cast<long double>("-2"), -2);
  EXPECT_THROW(romea::lexical_cast<int>("string"), std::invalid_argument);
}

//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToLongLong)
{
  EXPECT_EQ(romea::lexical_cast<long long>("10"), 10);
  EXPECT_EQ(romea::lexical_cast<long long>("-2"), -2);
  EXPECT_THROW(romea::lexical_cast<long long>("10000000000000000000"), std::out_of_range);
  EXPECT_THROW(romea::lexical_cast<long long>("3.14"), std::invalid_argument);
  EXPECT_THROW(romea::lexical_cast<long long>("string"), std::invalid_argument);
}

//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToUnsignedLong)
{
  EXPECT_EQ(romea::lexical_cast<unsigned long>("10"), 10);
  EXPECT_EQ(romea::lexical_cast<unsigned long>("-4"), static_cast<unsigned long>(-4));
  EXPECT_THROW(
    romea::lexical_cast<unsigned long>(
      "100000000000000000000000000000000000000000"), std::out_of_range);
  EXPECT_THROW(romea::lexical_cast<unsigned long>("3.14"), std::invalid_argument);
  EXPECT_THROW(romea::lexical_cast<unsigned long>("string"), std::invalid_argument);
}

//-----------------------------------------------------------------------------
TEST(TestLexical, testStringToUnsignedLongLong)
{
  EXPECT_EQ(romea::lexical_cast<unsigned long long>("10"), 10);
  EXPECT_EQ(romea::lexical_cast<unsigned long long>("-100"), static_cast<unsigned long long>(-100));
  EXPECT_THROW(
    romea::lexical_cast<unsigned long long>(
      "100000000000000000000000000000000000000000"), std::out_of_range);
  EXPECT_THROW(romea::lexical_cast<unsigned long long>("3.14"), std::invalid_argument);
  EXPECT_THROW(romea::lexical_cast<unsigned long long>("string"), std::invalid_argument);
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
