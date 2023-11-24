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
#include "romea_core_common/geometry/Position2D.hpp"

namespace romea
{
namespace core
{

//--------------------------------------------------------------------------
Position2D::Position2D()
: position(Eigen::Vector2d::Zero()),
  covariance(Eigen::Matrix2d::Zero())
{
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const Position2D & position2d)
{
  os << " Position 2D :" << std::endl;
  os << " position.x =" << position2d.position.x() << std::endl;
  os << " position.y =" << position2d.position.y() << std::endl;
  os << " covariance " << std::endl;
  os << position2d.covariance << std::endl;
  return os;
}

//--------------------------------------------------------------------------
// Position2D Position2D::toBody(const Pose2D &referenceFramePose)const
//{


//  SmartInverseRigidTransformation2D nedToBody(referenceFramePose.getPositionVector(),
//                                              referenceFramePose.getOrientationAroundZDownAxis(),
//                                              referenceFramePose.getCovariance());


//  CartesianCoordinates2d bodyPosition;
//  Eigen::Matrix2d bodyPositionCovariance;
//  nedToBody(position_,covariance_,bodyPosition,bodyPositionCovariance);
//  //TODO use std::move when eigen support will be available
//  return BodyPosition2D(bodyPosition,bodyPositionCovariance);

//}

//--------------------------------------------------------------------------
Ellipse uncertaintyEllipse(
  const Position2D & position2d,
  const double & sigmaScale)
{
  return Ellipse(
    position2d.position,
    position2d.covariance,
    sigmaScale);
}


}   // namespace core
}   // namespace romea
