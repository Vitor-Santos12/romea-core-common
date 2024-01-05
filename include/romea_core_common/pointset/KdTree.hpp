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


#ifndef ROMEA_CORE_COMMON__POINTSET__KDTREE_HPP_
#define ROMEA_CORE_COMMON__POINTSET__KDTREE_HPP_

// std
#include <vector>

// romea
#include "romea_core_common/pointset/kdtree/NanoFlannAdaptor.hpp"
#include "romea_core_common/pointset/PointTraits.hpp"

namespace romea
{
namespace core
{

template<class PointType>
class KdTree
{
public:
  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

public:
  explicit KdTree(const PointSet<PointType> & points);

  void findNearestNeighbor(
    const PointType & point,
    size_t & neighboorIndex,
    Scalar & neighboorSquareDistance)const;

  void findNearestNeighbors(
    const PointType & point,
    const size_t & numberOfNeighbors,
    std::vector<size_t> & neighboorIndexes,
    std::vector<Scalar> & neighboorSquareDistances)const;

  void radiusResearch(
    const PointType & point,
    const Scalar & radius,
    std::vector<size_t> & neighboorIndexes,
    std::vector<Scalar> & neighboorSquareDistances);

public:
  NanoFlannAdaptor<PointType, nanoflann::metric_L2> kdtree_;

  mutable nanoflann::KNNResultSet<Scalar> singleNNResult_;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__KDTREE_HPP_
