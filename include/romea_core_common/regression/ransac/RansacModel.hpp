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


#ifndef ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACMODEL_HPP_
#define ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACMODEL_HPP_

// stl
#include <cstddef>

namespace romea
{
namespace core
{

// TODO(jean) perhaps use crtp here

class RansacModel
{
public:
  RansacModel();

  virtual ~RansacModel() = default;

  virtual bool draw(const double & modelDeviationError) = 0;

  virtual size_t countInliers(const double & modelDeviationError) = 0;

  virtual void refine() = 0;

  virtual size_t getNumberOfPoints() const = 0;

  virtual size_t getNumberOfPointsToDrawModel() const = 0;

  virtual size_t getMinimalNumberOfInliers() const = 0;

  virtual double getRootMeanSquareError() const = 0;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACMODEL_HPP_
