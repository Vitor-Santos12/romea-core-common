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

// Eigen
#include <Eigen/Eigen>

// std
#include <random>

// romea
#include "romea_core_common/monitoring/OnlineVariance.hpp"

//-----------------------------------------------------------------------------
TEST(TestMonitoring, onlineVariance)
{
  double mean = -1;
  double std = 0.2;
  double average_precision = 0.0001;
  size_t N = 10000;

  std::mt19937 randomEngine(std::random_device{} ());
  std::normal_distribution<double> normalDistribution(mean, std);

  romea::OnlineAverage onlineAverage(average_precision, N);
  romea::OnlineVariance onlineVariance(average_precision, N);
  onlineAverage.update(0);
  onlineVariance.update(0);

  Eigen::ArrayXd data(N);
  for (size_t n = 0; n < N; ++n) {
    data(n) = normalDistribution(randomEngine);
    onlineAverage.update(data(n));
    onlineVariance.update(data(n));
  }


  EXPECT_EQ(onlineAverage.isAvailable(), true);
  EXPECT_EQ(onlineVariance.isAvailable(), true);

  EXPECT_NEAR(mean, onlineAverage.getAverage(), 0.01);
  EXPECT_NEAR(mean, onlineVariance.getAverage(), 0.01);
  EXPECT_NEAR(std, std::sqrt(onlineVariance.getVariance()), 0.01);

  onlineAverage.reset();
  onlineVariance.reset();
  EXPECT_EQ(onlineAverage.isAvailable(), false);
  EXPECT_EQ(onlineVariance.isAvailable(), false);
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
