// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST3D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST3D_HPP_

// romea
#include "romea_core_common/geometry/Pose3D.hpp"
#include "romea_core_common/geometry/Twist3D.hpp"
#include "romea_core_common/geometry/PoseAndTwist2D.hpp"

namespace romea
{

struct PoseAndTwist3D
{
  PoseAndTwist3D();

  Pose3D pose;
  Twist3D twist;
};

PoseAndTwist2D toPoseAndTwist2D(const PoseAndTwist3D & poseAndTwist3D);

void toPoseAndTwist2D(const PoseAndTwist3D & poseAndTwist3D, PoseAndTwist2D & poseAndTwist2D);

std::ostream & operator<<(std::ostream & os, const PoseAndTwist3D & poseAndTwist3D);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST3D_HPP_
