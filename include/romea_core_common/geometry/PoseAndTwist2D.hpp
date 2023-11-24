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


#ifndef ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST2D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST2D_HPP_

// romea
#include "romea_core_common/geometry/Pose2D.hpp"
#include "romea_core_common/geometry/Twist2D.hpp"

namespace romea
{
namespace core
{

struct PoseAndTwist2D
{
  PoseAndTwist2D();

  Pose2D pose;
  Twist2D twist;
};

std::ostream & operator<<(std::ostream & os, const PoseAndTwist2D & poseAndBodyTwist2D);

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__POSEANDTWIST2D_HPP_
