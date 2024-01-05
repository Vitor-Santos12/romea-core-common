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


#ifndef ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__POINTSETPRECONDITIONER_HPP_
#define ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__POINTSETPRECONDITIONER_HPP_

// Eigen
#include <unsupported/Eigen/MatrixFunctions>

// romea
#include "romea_core_common/pointset/PointSet.hpp"
#include "romea_core_common/pointset/PointTraits.hpp"

namespace romea
{
namespace core
{

template<class PointType>
class PointSetPreconditioner
{
public:
  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using TranslationVector = Eigen::Matrix<Scalar, CARTESIAN_DIM, 1>;

public:
  PointSetPreconditioner();

  explicit PointSetPreconditioner(const PointSet<PointType> & points);

  void compute(const PointSet<PointType> & points);

  const PointType & getPointSetMean()const;

  const PointType & getPointSetMin()const;

  const PointType & getPointSetMax()const;

  const Scalar & getScale()const;

  const TranslationVector & getTranslation() const;

private:
  Scalar scale_;
  TranslationVector translation_;

  PointType pointSetMean_;
  PointType pointSetMin_;
  PointType pointSetMax_;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF_VECTORIZABLE_FIXED_SIZE(Scalar, POINT_SIZE)
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__POINTSETPRECONDITIONER_HPP_
