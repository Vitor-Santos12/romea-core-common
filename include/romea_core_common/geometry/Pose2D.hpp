// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__POSE2D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__POSE2D_HPP_

#include "romea_core_common/geometry/Ellipse.hpp"

namespace romea
{

struct Pose2D
{
  Pose2D();

  double yaw;
  Eigen::Vector2d position;
  Eigen::Matrix3d covariance;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

Ellipse uncertaintyEllipse(
  const Pose2D & pose2d,
  const double & sigmaScale);

std::ostream & operator<<(std::ostream & os, const Pose2D & pose2D);

}  // namespace romea


#endif  // ROMEA_CORE_COMMON__GEOMETRY__POSE2D_HPP_
