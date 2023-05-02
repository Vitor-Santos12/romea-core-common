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


#ifndef ROMEA_CORE_COMMON__CONTAINERS__EIGEN__EIGENCONTAINERS_HPP_
#define ROMEA_CORE_COMMON__CONTAINERS__EIGEN__EIGENCONTAINERS_HPP_

// std
#include <limits>
#include <algorithm>

// romea
#include "romea_core_common/containers/Eigen/DequeOfEigenVector.hpp"
#include "romea_core_common/containers/Eigen/ListOfEigenVector.hpp"
#include "romea_core_common/containers/Eigen/VectorOfEigenVector.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
template<class EigenContainerType>
typename EigenContainerType::value_type
min(const EigenContainerType & points)
{
  using PointType = typename EigenContainerType::value_type;

  PointType minimalCoordinates =
    PointType::Constant(std::numeric_limits<typename PointType::Scalar>::max());

  for (auto point : points) {
    minimalCoordinates = minimalCoordinates.min(point);
  }

  return minimalCoordinates;
}

//-----------------------------------------------------------------------------
template<class EigenContainerType>
typename EigenContainerType::value_type
max(const EigenContainerType & points)
{
  using PointType = typename EigenContainerType::value_type;

  PointType maximalCoordinates =
    PointType::Constant(-std::numeric_limits<typename PointType::Scalar>::max());

  for (auto point : points) {
    maximalCoordinates = maximalCoordinates.max(point);
  }

  return maximalCoordinates;
}

//-----------------------------------------------------------------------------
template<class EigenContainerType>
typename EigenContainerType::value_type
mean(const EigenContainerType & points)
{
  using PointType = typename EigenContainerType::value_type;

  PointType meanCoordinates = PointType::Zero();
  for (auto point : points) {
    meanCoordinates += point;
  }
  meanCoordinates /= points.size();
  return meanCoordinates;
}

//-----------------------------------------------------------------------------
template<class EigenContainerType>
void transform(
  const EigenContainerType & sourcePoints,
  EigenContainerType & targetPoints,
  const Eigen::Matrix<typename EigenContainerType::value_type::Scalar,
  Eigen::internal::traits<typename EigenContainerType::value_type>::RowsAtCompileTime,
  Eigen::internal::traits<typename EigenContainerType::value_type>::RowsAtCompileTime> & rotation,
  const Eigen::Matrix<typename EigenContainerType::value_type::Scalar,
  Eigen::internal::traits<typename EigenContainerType::value_type>::RowsAtCompileTime,
  1> & translation)
{
  targetPoints.resize(sourcePoints.size());
  auto itSource = std::cbegin(sourcePoints);
  auto itTarget = std::begin(targetPoints);

  for (; itSource != sourcePoints.end(); ++itSource, ++itTarget) {
    (*itTarget) = rotation * (*itSource) + translation;
  }
}


}  // namespace romea

#endif  // ROMEA_CORE_COMMON__CONTAINERS__EIGEN__EIGENCONTAINERS_HPP_
