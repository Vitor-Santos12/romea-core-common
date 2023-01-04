// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include "romea_core_common/geometry/Position3D.hpp"

namespace romea
{

//--------------------------------------------------------------------------
Position3D::Position3D()
: position(Eigen::Vector3d::Zero()),
  covariance(Eigen::Matrix3d::Zero())
{
}

}   // namespace romea
