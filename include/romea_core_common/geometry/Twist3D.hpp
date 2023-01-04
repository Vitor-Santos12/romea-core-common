// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__TWIST3D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__TWIST3D_HPP_

// romea
#include "romea_core_common/geometry/Twist2D.hpp"
#include "romea_core_common/math/Matrix.hpp"

namespace romea
{

struct Twist3D
{
  Twist3D();

  Eigen::Vector3d linearSpeeds;
  Eigen::Vector3d angularSpeeds;
  Eigen::Matrix6d covariance;
};

Twist2D toTwist2D(const Twist3D & twist3d);

void toTwist2D(const Twist3D & twist3d, Twist2D & twist2d);

std::ostream & operator<<(std::ostream & os, const Twist3D & twist3D);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__TWIST3D_HPP_
