// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__POSITION2D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__POSITION2D_HPP_

// romea
#include "romea_core_common/geometry/Ellipse.hpp"

namespace romea
{

struct Position2D
{
  Position2D();

  Eigen::Vector2d position;
  Eigen::Matrix2d covariance;
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

Ellipse uncertaintyEllipse(
  const Position2D & position2d,
  const double & sigmaScale);

std::ostream & operator<<(std::ostream & os, const Position2D & position2d);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__POSITION2D_HPP_
