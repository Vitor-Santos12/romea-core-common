#ifndef ROMEA_CORE_COMMON_GEOMETRY_POSE3D_HPP_
#define ROMEA_CORE_COMMON_GEOMETRY_POSE3D_HPP_

// Eigen
#include <Eigen/Geometry>

// romea
#include "romea_core_common/geometry/Pose2D.hpp"
#include "romea_core_common/geometry/Position3D.hpp"
#include "romea_core_common/math/Matrix.hpp"

namespace romea {

struct Pose3D {
  Pose3D();

  Eigen::Vector3d position;
  Eigen::Vector3d orientation;
  Eigen::Matrix6d covariance;
};

Pose2D toPose2D(const Pose3D & pose3d);

Position3D toPosition3D(const Pose3D & pose3d);

void toPose2D(const Pose3D & pose3d, Pose2D & pose2d);

void toPosition3D(const Pose3D & pose3d, Position3D & position3d);

std::ostream & operator <<(std::ostream & os, const Pose3D & pose3D);

Pose3D operator*(const Eigen::Affine3d & affine, const Pose3D & pose3d);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_GEOMETRY_POSE3D_HPP_

