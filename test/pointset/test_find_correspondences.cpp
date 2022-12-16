// gtest
#include <gtest/gtest.h>
#include "test_helper.h"
#include "test_pointset_utils.hpp"

//-----------------------------------------------------------------------------
template <class PointType> size_t findCorrespondences(const std::string & dataFileName)
{
  // load data
  romea::PointSet<Eigen::Vector2d> pointSet = loadScan<Eigen::Vector2d>(dataFileName);
  romea::KdTree<Eigen::Vector2d> kdTree(pointSet);

  // Search nearest point;
  size_t nearestIndex;
  double nearestNeighborSquareDistance;
  std::vector<romea::Correspondence> correspondences;

  // Find correpondences
  for (size_t n = 0; n < pointSet.size(); ++n){
    kdTree.findNearestNeighbor(pointSet[n], nearestIndex, nearestNeighborSquareDistance);
    correspondences.emplace_back(nearestIndex, n, nearestNeighborSquareDistance);
  }

  // Remove wrong correspondences
  std::vector<romea::Correspondence>::iterator itEnd;
  std::sort(std::begin(correspondences),
            std::end(correspondences),
            romea::sortBySourceIndexAndDistancePredicate);

  itEnd = std::unique(std::begin(correspondences),
                      std::end(correspondences),
                      romea::equalSourceIndexesPredicate);

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
int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
