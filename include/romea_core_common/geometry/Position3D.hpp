#ifndef ROMEA_CORE_COMMON_GEOMETRY_POSITION3D_HPP_
#define ROMEA_CORE_COMMON_GEOMETRY_POSITION3D_HPP_

// Eigen
#include <Eigen/Core>

namespace romea {

struct Position3D {
  Position3D();

  Eigen::Vector3d position;
  Eigen::Matrix3d covariance;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_GEOMETRY_POSITION3D_HPP_
