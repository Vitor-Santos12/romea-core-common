// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__POSITION3D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__POSITION3D_HPP_

// Eigen
#include <Eigen/Core>

namespace romea {

struct Position3D {
  Position3D();

  Eigen::Vector3d position;
  Eigen::Matrix3d covariance;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__POSITION3D_HPP_
