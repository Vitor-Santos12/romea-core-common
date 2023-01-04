// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__COORDINATES__CARTESIANCOORDINATES_HPP_
#define ROMEA_CORE_COMMON__COORDINATES__CARTESIANCOORDINATES_HPP_

// Eigen
#include <Eigen/Core>

namespace romea
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

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__COORDINATES__CARTESIANCOORDINATES_HPP_
