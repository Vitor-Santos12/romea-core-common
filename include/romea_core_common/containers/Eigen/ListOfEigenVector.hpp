// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__CONTAINERS_EIGEN__LISTOFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON__CONTAINERS_EIGEN__LISTOFEIGENVECTOR_HPP_

// Eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdList>

// std
#include <list>


namespace romea
{

template<class EigenVectorType>
using ListOfEigenVector =
  std::list<EigenVectorType, Eigen::aligned_allocator<EigenVectorType>>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__CONTAINERS__EIGEN__LISTOFEIGENVECTOR_HPP_
