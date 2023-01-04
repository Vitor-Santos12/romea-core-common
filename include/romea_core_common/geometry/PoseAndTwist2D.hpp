// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST2D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST2D_HPP_

// romea
#include "romea_core_common/geometry/Pose2D.hpp"
#include "romea_core_common/geometry/Twist2D.hpp"

namespace romea
{

struct PoseAndTwist2D
{
  PoseAndTwist2D();

  Pose2D pose;
  Twist2D twist;
};

std::ostream & operator<<(std::ostream & os, const PoseAndTwist2D & poseAndBodyTwist2D);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST2D_HPP_
