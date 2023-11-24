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


// std
#include <vector>
#include <utility>

// romea
#include "romea_core_common/pointset/KdTree.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
template<class PointType>
KdTree<PointType>::KdTree(const PointSet<PointType> & points)
: kdtree_(points),
  singleNNResult_(1)
{
}

//-----------------------------------------------------------------------------
template<class PointType>
void KdTree<PointType>::findNearestNeighbor(
  const PointType & point,
  size_t & neighboorIndex,
  Scalar & neighboorSquareDistance)const
{
  singleNNResult_.init(&neighboorIndex, &neighboorSquareDistance);
  kdtree_.index->findNeighbors(singleNNResult_, &point[0], nanoflann::SearchParams(10));
}

//-----------------------------------------------------------------------------
template<class PointType>
void KdTree<PointType>::findNearestNeighbors(
  const PointType & point,
  const size_t & numberOfNeighbors,
  std::vector<size_t> & neighboorIndexes,
  std::vector<Scalar> & neighboorSquareDistances)const
{
  nanoflann::KNNResultSet<Scalar> resultSet(numberOfNeighbors);
  resultSet.init(&neighboorIndexes[0], &neighboorSquareDistances[0]);
  kdtree_.index->findNeighbors(resultSet, &point[0], nanoflann::SearchParams(10));
}

//-----------------------------------------------------------------------------
template<class PointType>
void KdTree<PointType>::radiusResearch(
  const PointType & point,
  const Scalar & distance,
  std::vector<size_t> & neighboorIndexes,
  std::vector<Scalar> & neighboorSquareDistances)
{
  std::vector<std::pair<size_t, Scalar>> results;
  size_t numberOfNeighBoors = kdtree_.index->radiusSearch(
    &point[0], distance, results, nanoflann::SearchParams(10));

  neighboorIndexes.resize(numberOfNeighBoors);
  neighboorSquareDistances.resize(numberOfNeighBoors);

  for (size_t n = 0; n < numberOfNeighBoors; ++n) {
    neighboorIndexes[n] = results[n].first;
    neighboorSquareDistances[n] = results[n].second;
  }
}


template class KdTree<Eigen::Vector2f>;
template class KdTree<Eigen::Vector2d>;
template class KdTree<Eigen::Vector3f>;
template class KdTree<Eigen::Vector3d>;
template class KdTree<HomogeneousCoordinates2f>;
template class KdTree<HomogeneousCoordinates2d>;
template class KdTree<HomogeneousCoordinates3f>;
template class KdTree<HomogeneousCoordinates3d>;

}   // namespace core
}   // namespace romea
