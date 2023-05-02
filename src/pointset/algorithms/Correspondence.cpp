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
#include "romea_core_common/pointset/algorithms/Correspondence.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
Correspondence::Correspondence()
: Correspondence(0, 0, 0, 1)
{
}

//-----------------------------------------------------------------------------
Correspondence::Correspondence(
  const size_t & sourcePointIndex,
  const size_t & targetPointIndex)
: Correspondence(sourcePointIndex, targetPointIndex, 0., 1)
{
}

//-----------------------------------------------------------------------------
Correspondence::Correspondence(
  const size_t & sourcePointIndex,
  const size_t & targetPointIndex,
  const double & squareDistanceBetweenPoints)
: Correspondence(sourcePointIndex, targetPointIndex, squareDistanceBetweenPoints, 1)
{
}

//-----------------------------------------------------------------------------
Correspondence::Correspondence(
  const size_t & sourcePointIndex_,
  const size_t & targetPointIndex_,
  const double & squareDistanceBetweenPoints_,
  const double & weight_)
: sourcePointIndex(sourcePointIndex_),
  targetPointIndex(targetPointIndex_),
  squareDistanceBetweenPoints(squareDistanceBetweenPoints_),
  weight(weight_)
{
}

}   // namespace romea
