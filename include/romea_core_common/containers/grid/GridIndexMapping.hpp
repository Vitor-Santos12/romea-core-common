// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__CONTAINERS__GRID__GRIDINDEXMAPPING_HPP_
#define ROMEA_CORE_COMMON__CONTAINERS__GRID__GRIDINDEXMAPPING_HPP_

// Eigen
#include <Eigen/Core>

// std
#include <cstddef>
#include <vector>

// Romea
#include "romea_core_common/math/Interval.hpp"

namespace romea
{

template<typename Scalar, size_t DIM>
class GridIndexMapping
{
public:
  using IntervalType = Interval<Scalar, DIM>;
  using PointType = Eigen::Matrix<Scalar, DIM, 1>;
  using CellIndexes = Eigen::Matrix<size_t, DIM, 1>;

public:
  GridIndexMapping();

  GridIndexMapping(
    const Scalar & maximalRange,
    const Scalar & cellResolution);

  GridIndexMapping(
    const IntervalType & extremities,
    const Scalar & cellResolution);

public:
  const Scalar & getCellResolution()const;

  const CellIndexes & getNumberOfCellsAlongAxes()const;

  const std::vector<Scalar> & getCellCentersPositionAlong(const size_t & axisDIM) const;

public:
  CellIndexes computeCellIndexes(const PointType & point) const;

  PointType computeCellCenterPosition(const CellIndexes & cellIndexes) const;

private:
  Scalar cellResolution_;
  CellIndexes numberOfCellsAlongAxes_;
  PointType flooredMinimalPositionAlongAxes_;
  std::vector<std::vector<Scalar>> cellCentersPositionAlongAxes_;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF_VECTORIZABLE_FIXED_SIZE(Scalar, DIM)
};

using GridIndexMapping2f = GridIndexMapping<float, 2>;
using GridIndexMapping3f = GridIndexMapping<float, 3>;
using GridIndexMapping2d = GridIndexMapping<double, 2>;
using GridIndexMapping3d = GridIndexMapping<double, 3>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_GRID_GRIDINDEXMAPPING_HPP_
