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
#include "romea_core_common/geometry/Ellipse.hpp"

// eigen
#include <Eigen/SVD>

namespace romea
{

//-----------------------------------------------------------------------------
Ellipse::Ellipse(
  const double & xCenter,
  const double & yCenter,
  const double & orientation,
  const double & majorRadius,
  const double & minorRadius)
: centerPosition_((Eigen::Vector2d() << xCenter, yCenter).finished()),
  orientation_(orientation),
  majorRadius_(majorRadius),
  minorRadius_(minorRadius)
{
}

//-----------------------------------------------------------------------------
Ellipse::Ellipse(
  const Eigen::Vector2d & centerPosition,
  const double & orientation,
  const double & majorRadius,
  const double & minorRadius)
: centerPosition_(centerPosition),
  orientation_(orientation),
  majorRadius_(majorRadius),
  minorRadius_(minorRadius)
{
}

//-----------------------------------------------------------------------------
Ellipse::Ellipse(
  const Eigen::Vector2d & centerPosition,
  const Eigen::Matrix2d & covarianceMatrix,
  const double & sigmaScale)
: centerPosition_(centerPosition),
  orientation_(0),
  majorRadius_(0),
  minorRadius_(0)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(covarianceMatrix, Eigen::ComputeThinU);
  Eigen::Vector2d singularValues = svd.singularValues();
  Eigen::Matrix2d singularVectors = svd.matrixU();

  orientation_ = std::atan2(singularVectors(1, 0), singularVectors(0, 0));
  majorRadius_ = std::sqrt(singularValues(0)) * sigmaScale;
  minorRadius_ = std::sqrt(singularValues(1)) * sigmaScale;
}

//-----------------------------------------------------------------------------
const Eigen::Vector2d & Ellipse::getCenterPosition()const
{
  return centerPosition_;
}

const double & Ellipse::getOrientation()const
{
  return orientation_;
}

const double & Ellipse::getMajorRadius()const
{
  return majorRadius_;
}

const double & Ellipse::getMinorRadius()const
{
  return minorRadius_;
}

}   // namespace romea
