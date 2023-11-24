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


#ifndef ROMEA_CORE_COMMON__GEOMETRY__ELLIPSE_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__ELLIPSE_HPP_

// Eigen
#include <Eigen/Core>

namespace romea
{
namespace core
{

class Ellipse
{
public:
  Ellipse(
    const double & xCenter,
    const double & yCenter,
    const double & orientation,
    const double & majorRadius,
    const double & minorRadius);

  Ellipse(
    const Eigen::Vector2d & centerPosition,
    const double & orientation,
    const double & majorRadius,
    const double & minorRadius);

  Ellipse(
    const Eigen::Vector2d & centerPosition,
    const Eigen::Matrix2d & covarianceMatrix,
    const double & sigmaScale);

public:
  const Eigen::Vector2d & getCenterPosition()const;

  const double & getOrientation()const;

  const double & getMajorRadius()const;

  const double & getMinorRadius()const;

protected:
  Eigen::Vector2d centerPosition_;
  double orientation_;
  double majorRadius_;
  double minorRadius_;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

}  // namespace core
}  // namespace romea


#endif  // ROMEA_CORE_COMMON__GEOMETRY__ELLIPSE_HPP_
