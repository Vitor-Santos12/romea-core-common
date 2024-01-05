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

// std
#include <string>
#include <vector>

// local
#include "../test/test_helper.h"
#include "test_pointset_utils.hpp"

//-----------------------------------------------------------------------------
template<class PointType>
size_t findCorrespondences(const std::string & dataFileName)
{
  // load data
  romea::core::PointSet<Eigen::Vector2d> pointSet = loadScan<Eigen::Vector2d>(dataFileName);
  romea::core::KdTree<Eigen::Vector2d> kdTree(pointSet);

  // Search nearest point;
  size_t nearestIndex;
  double nearestNeighborSquareDistance;
  std::vector<romea::core::Correspondence> correspondences;

  // Find correpondences
  for (size_t n = 0; n < pointSet.size(); ++n) {
    kdTree.findNearestNeighbor(pointSet[n], nearestIndex, nearestNeighborSquareDistance);
    correspondences.emplace_back(nearestIndex, n, nearestNeighborSquareDistance);
  }

  // Remove wrong correspondences
  std::vector<romea::core::Correspondence>::iterator itEnd;
  std::sort(
    std::begin(correspondences),
    std::end(correspondences),
    romea::core::sortBySourceIndexAndDistancePredicate);

  itEnd = std::unique(
    std::begin(correspondences),
    std::end(correspondences),
    romea::core::equalSourceIndexesPredicate);

  return static_cast<size_t>(std::distance(std::begin(correspondences), itEnd));
}

//-----------------------------------------------------------------------------
TEST(TestFindCorrespondences, find2DCorrespondences)
{
  EXPECT_EQ(702, findCorrespondences<Eigen::Vector2d>("/scan2d.txt"));
}

//-----------------------------------------------------------------------------
TEST(TestFindCorrespondences, find3DCorrespondences)
{
  EXPECT_EQ(99426, findCorrespondences<Eigen::Vector3d>("/scan3d.txt"));
}

//-----------------------------------------------------------------------------
int main(int argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
