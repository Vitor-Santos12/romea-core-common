// gtest
#include <gtest/gtest.h>
#
//romea
#include "romea_core_common/monitoring/RateMonitoring.hpp"

//-----------------------------------------------------------------------------
TEST(TestMonitoring, rate)
{
  double expectedRate=10;
  romea::RateMonitoring rateMonitoring(expectedRate);

  romea::Duration stamp = romea::durationFromSecond(0);
  EXPECT_DOUBLE_EQ(rateMonitoring.update(stamp),0.);

  for(size_t n=1;n<2/static_cast<size_t>(expectedRate);++n)
  {
    romea::Duration  stamp = romea::durationFromSecond(n/expectedRate);
    EXPECT_DOUBLE_EQ(rateMonitoring.update(stamp),expectedRate);
  }

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
