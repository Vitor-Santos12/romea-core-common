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
