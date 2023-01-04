// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__POINTSET__NORMALSET_HPP_
#define ROMEA_CORE_COMMON__POINTSET__NORMALSET_HPP_

#include "../containers/Eigen/VectorOfEigenVector.hpp"

namespace romea
{

template<class PointType>
using NormalSet = VectorOfEigenVector<PointType>;

}   // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__NORMALSET_HPP_
