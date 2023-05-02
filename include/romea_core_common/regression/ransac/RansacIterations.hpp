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


#ifndef ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACITERATIONS_HPP_
#define ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACITERATIONS_HPP_

// std
#include <cstddef>

namespace romea
{

class RansacIterations
{
public:
  RansacIterations(
    const size_t & numberOfPoints,
    const float & fittingProbability,
    const size_t & maximalNumberOfIterations);

  void update(
    const size_t & numberOfInliers,
    const size_t & numberOfPointsToDrawModel);

  double get() const;

private:
  double logOfFittingOppositeProbability_;
  double oneOverNumberOfPoints_;
  double numberOfIterations_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACITERATIONS_HPP_
