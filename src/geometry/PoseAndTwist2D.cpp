// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include "romea_core_common/geometry/PoseAndTwist2D.hpp"

namespace romea
{

//--------------------------------------------------------------------------
PoseAndTwist2D::PoseAndTwist2D()
: pose(),
  twist()
{
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const PoseAndTwist2D & poseAndBodyTwist2D)
{
  os << poseAndBodyTwist2D.pose;
  os << poseAndBodyTwist2D.twist;
  return os;
}

}   // namespace romea
