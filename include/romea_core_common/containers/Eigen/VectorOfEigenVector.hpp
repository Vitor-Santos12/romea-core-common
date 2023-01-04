// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__CONTAINERS__EIGEN__VECTOROFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON__CONTAINERS__EIGEN__VECTOROFEIGENVECTOR_HPP_

// eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdVector>

// std
#include <vector>

namespace romea
{

template<class EigenVectorType>
using VectorOfEigenVector =
  std::vector<EigenVectorType, Eigen::aligned_allocator<EigenVectorType>>;

using VectorOfEigenVector2d = VectorOfEigenVector<Eigen::Vector2d>;
using VectorOfEigenVector3d = VectorOfEigenVector<Eigen::Vector3d>;
using VectorOfEigenVector4d = VectorOfEigenVector<Eigen::Vector4d>;

using VectorOfEigenVector2f = VectorOfEigenVector<Eigen::Vector2f>;
using VectorOfEigenVector3f = VectorOfEigenVector<Eigen::Vector3f>;
using VectorOfEigenVector4f = VectorOfEigenVector<Eigen::Vector4f>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__CONTAINERS__EIGEN__VECTOROFEIGENVECTOR_HPP_
