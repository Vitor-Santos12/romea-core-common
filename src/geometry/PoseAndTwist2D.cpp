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
#include "romea_core_common/geometry/PoseAndTwist2D.hpp"

namespace romea
{
namespace core
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

}   // namespace core
}   // namespace romea
