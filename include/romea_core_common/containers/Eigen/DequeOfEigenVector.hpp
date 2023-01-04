// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__CONTAINERS__EIGEN__DEQUEOFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON__CONTAINERS__EIGEN__DEQUEOFEIGENVECTOR_HPP_

// eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdDeque>

// std
#include <vector>


namespace romea
{

template<class EigenVectorType>
using DequeOfEigenVector =
  std::vector<EigenVectorType, Eigen::aligned_allocator<EigenVectorType>>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_EIGEN_DEQUEOFEIGENVECTOR_HPP_
