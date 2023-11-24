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


#ifndef ROMEA_CORE_COMMON__COORDINATES__CARTESIANCOORDINATES_HPP_
#define ROMEA_CORE_COMMON__COORDINATES__CARTESIANCOORDINATES_HPP_

// Eigen
#include <Eigen/Core>

namespace romea
{
namespace core
{

template<typename Scalar>
using CartesianCoordinates2 = Eigen::Matrix<Scalar, 2, 1>;
template<typename Scalar>
using CartesianCoordinates3 = Eigen::Matrix<Scalar, 3, 1>;

using CartesianCoordinates2f = CartesianCoordinates2<float>;
using CartesianCoordinates2d = CartesianCoordinates2<double>;
using CartesianPoint2f = CartesianCoordinates2<float>;
using CartesianPoint2d = CartesianCoordinates2<double>;

using CartesianCoordinates3f = CartesianCoordinates3<float>;
using CartesianCoordinates3d = CartesianCoordinates3<double>;
using CartesianPoint3f = CartesianCoordinates3<float>;
using CartesianPoint3d = CartesianCoordinates3<double>;

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__COORDINATES__CARTESIANCOORDINATES_HPP_
