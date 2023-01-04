// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__POINTSET__KDTREE_HPP_
#define ROMEA_CORE_COMMON__POINTSET__KDTREE_HPP_

// std
#include <vector>

// romea
#include "romea_core_common/pointset/kdtree/NanoFlannAdaptor.hpp"
#include "romea_core_common/pointset/PointTraits.hpp"

namespace romea
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

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__KDTREE_HPP_
