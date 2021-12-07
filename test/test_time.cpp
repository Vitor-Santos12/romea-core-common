// gtest
#include <gtest/gtest.h>

//romea
#include "romea_core_common/time/Time.hpp"

//-----------------------------------------------------------------------------
TEST(TestTime, convertion)
{
  romea::Duration sec(1000000000);

  EXPECT_EQ(romea::durationFromNanoSecond(1000000000).count(),sec.count());
  EXPECT_EQ(romea::durationFromMicroSecond(1000000).count(),sec.count());
  EXPECT_EQ(romea::durationFromMilliSecond(1000).count(),sec.count());
  EXPECT_EQ(romea::durationFromSecond(1).count(),sec.count());

  EXPECT_EQ(romea::durationToNanoSecond(sec),1000000000);
  EXPECT_EQ(romea::durationToMicroSecond(sec),1000000);
  EXPECT_EQ(romea::durationToMilliSecond(sec),1000);
  EXPECT_EQ(romea::durationToSecond(sec),1);

}

//-----------------------------------------------------------------------------
TEST(TestTime, makeDuration)
{
  EXPECT_EQ(romea::makeDuration(1,3,43.9).count(),3823900000000);
  EXPECT_EQ(romea::makeDuration(24,0,1.).count(),86401000000000);
}

//-----------------------------------------------------------------------------
TEST(TestTime, durationToString)
{
  EXPECT_STREQ(romea::asString(romea::durationFromSecond(3823.1000)).c_str(),"01:03:43.9");
  EXPECT_STREQ(romea::asString(romea::durationFromSecond(86401)).c_str(),"24:00:01.0");
}

//-----------------------------------------------------------------------------
TEST(TestTime, DISABLED_makeTimePoint)
{
  EXPECT_EQ(romea::makeTimePoint(1977,7,17,4,30,7.7).time_since_epoch().count(),237954607000000000);
  EXPECT_EQ(romea::makeTimePoint(2016,3,12,8,20,50.7).time_since_epoch().count(),1457767250000000000);
}

//-----------------------------------------------------------------------------
TEST(TestTime, timePointToString)
{
  EXPECT_STREQ(romea::asString(romea::makeTimePoint(1977,7,17,4,30,7.7)).c_str(),"Sun Jul 17 04:30:07 1977");
  EXPECT_STREQ(romea::asString(romea::makeTimePoint(2016,3,12,8,20,50.7)).c_str(),"Sat Mar 12 08:20:50 2016");
}
//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
