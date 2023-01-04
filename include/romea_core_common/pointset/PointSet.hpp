// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__POINTSET__POINTSET_HPP_
#define ROMEA_CORE_COMMON__POINTSET__POINTSET_HPP_

// romea
#include "romea_core_common/coordinates/CartesianCoordinates.hpp"
#include "romea_core_common/coordinates/HomogeneousCoordinates.hpp"
#include "romea_core_common/containers/Eigen/VectorOfEigenVector.hpp"

namespace romea
{

template<class PointType>
using PointSet = VectorOfEigenVector<PointType>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__POINTSET_HPP_
