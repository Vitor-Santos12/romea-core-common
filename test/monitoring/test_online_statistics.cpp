// gtest
#include <gtest/gtest.h>
#
//romea
#include "romea_common/monitoring/RateMonitoring.hpp"
#include "romea_common/monitoring/OnlineVariance.hpp"

//std
#include <random>

//Eigen
#include <Eigen/Eigen>


//-----------------------------------------------------------------------------
TEST(TestMonitoring, onlineVariance)
{

  double mean = -1;
  double std = 0.2;
  double average_precision=0.0001;
  size_t N=10000;

  std::mt19937 randomEngine(std::random_device{}());
  std::normal_distribution<double> normalDistribution(mean,std);

  romea::OnlineAverage onlineAverage(average_precision,N);
  romea::OnlineVariance onlineVariance(average_precision,N);
  onlineAverage.update(0);
  onlineVariance.update(0);

  Eigen::ArrayXd data(N);
  for(size_t n=0;n<N;++n)
  {
    data(n)= normalDistribution(randomEngine);
    onlineAverage.update(data(n));
    onlineVariance.update(data(n));
  }


  EXPECT_EQ(onlineAverage.isAvailable(),true);
  EXPECT_EQ(onlineVariance.isAvailable(),true);

  EXPECT_NEAR(mean,onlineAverage.getAverage(),0.01);
  EXPECT_NEAR(mean,onlineVariance.getAverage(),0.01);
  EXPECT_NEAR(std,std::sqrt(onlineVariance.getVariance()),0.01);
}


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