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


#include "romea_core_common/geometry/Twist2D.hpp"

namespace romea
{

//--------------------------------------------------------------------------
Twist2D::Twist2D()
: angularSpeed(0),
  linearSpeeds(Eigen::Vector2d::Zero()),
  covariance(Eigen::Matrix3d::Zero())
{
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Twist2D & twist2D)
{
  os << " Twist 2D :" << std::endl;
  os << " linear.x =" << twist2D.linearSpeeds.x() << std::endl;
  os << " linear.y =" << twist2D.linearSpeeds.y() << std::endl;
  os << " angular.z =" << twist2D.angularSpeed << std::endl;
  os << " covariance " << std::endl;
  os << twist2D.covariance << std::endl;
  return os;
}

}   // namespace romea
