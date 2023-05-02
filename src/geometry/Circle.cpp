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
#include "romea_core_common/geometry/Circle.hpp"

namespace romea
{


//-----------------------------------------------------------------------------
Circle::Circle(
  const double & xCenter,
  const double & yCenter,
  const double & radius)
: centerPosition_(Eigen::Vector2d(xCenter, yCenter)),
  radius_(radius)
{
}

//-----------------------------------------------------------------------------
Circle::Circle(
  const Eigen::Vector2d & centerPosition,
  const double & radius)
: centerPosition_(centerPosition),
  radius_(radius)
{
}

//-----------------------------------------------------------------------------
const Eigen::Vector2d & Circle::getCenterPosition()const
{
  return centerPosition_;
}

//-----------------------------------------------------------------------------
const double & Circle::getRadius()const
{
  return radius_;
}

}  // namespace romea
