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
TEST(TestMonitoring, testOnlineVariance)
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
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
