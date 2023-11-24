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


#include "romea_core_common/geometry/PoseAndTwist3D.hpp"

namespace romea
{
namespace core
{

//--------------------------------------------------------------------------
PoseAndTwist3D::PoseAndTwist3D()
: pose(),
  twist()
{
}

//--------------------------------------------------------------------------
PoseAndTwist2D toPoseAndTwist2D(const PoseAndTwist3D & poseAndTwist3D)
{
  PoseAndTwist2D poseAndTwist2D;
  toPoseAndTwist2D(poseAndTwist3D, poseAndTwist2D);
  return poseAndTwist2D;
}

//--------------------------------------------------------------------------
void toPoseAndTwist2D(
  const PoseAndTwist3D & poseAndTwist3D,
  PoseAndTwist2D & poseAndTwist2D)
{
  toPose2D(poseAndTwist3D.pose, poseAndTwist2D.pose);
  toTwist2D(poseAndTwist3D.twist, poseAndTwist2D.twist);
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const PoseAndTwist3D & poseAndTwist3D)
{
  os << poseAndTwist3D.pose;
  os << poseAndTwist3D.twist;
  return os;
}

}   // namespace core
}   // namespace romea
