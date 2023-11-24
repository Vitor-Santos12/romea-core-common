// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


// romea
#include "romea_core_common/geometry/Pose2D.hpp"
#include "romea_core_common/geometry/Position2D.hpp"
#include "romea_core_common/math/EulerAngles.hpp"

namespace romea
{
namespace core
{

//--------------------------------------------------------------------------
Pose2D::Pose2D()
: yaw(0),
  position(Eigen::Vector2d::Zero()),
  covariance(Eigen::Matrix3d::Zero())
{
}

//--------------------------------------------------------------------------
Ellipse uncertaintyEllipse(
  const Pose2D & pose2d,
  const double & sigmaScale)
{
  return Ellipse(
    pose2d.position,
    pose2d.covariance.block<2, 2>(0, 0),
    sigmaScale);
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Pose2D & pose2D)
{
  os << " Pose 2D :" << std::endl;
  os << " x =" << pose2D.position.x() << std::endl;
  os << " y =" << pose2D.position.y() << std::endl;
  os << " yaw " << pose2D.yaw << std::endl;
  os << " covariance " << std::endl;
  os << pose2D.covariance << std::endl;

  return os;
}

}  // namespace core
}  // namespace romea
