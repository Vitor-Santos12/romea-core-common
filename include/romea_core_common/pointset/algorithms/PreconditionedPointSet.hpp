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


#ifndef ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__PRECONDITIONEDPOINTSET_HPP_
#define ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__PRECONDITIONEDPOINTSET_HPP_

// romea
#include "romea_core_common/pointset/PointSet.hpp"
#include "romea_core_common/pointset/algorithms/PointSetPreconditioner.hpp"

namespace romea
{
namespace core
{

template<class PointType>
class PreconditionedPointSet
{
public:
  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using TranslationVector = Eigen::Matrix<Scalar, CARTESIAN_DIM, 1>;
  using ScaleMatrix = Eigen::Matrix<Scalar, CARTESIAN_DIM, CARTESIAN_DIM>;
  using TransformationMatrix = Eigen::Matrix<Scalar, CARTESIAN_DIM + 1, CARTESIAN_DIM + 1>;
  using PointSetPreconditionerType = PointSetPreconditioner<PointType>;

public:
  PreconditionedPointSet();

  PreconditionedPointSet(
    const PointSet<PointType> & points,
    const PointSetPreconditionerType & preconditioner);

  PreconditionedPointSet(
    const PointSet<PointType> & points,
    const Scalar & preconditioningScale);

  PreconditionedPointSet(
    const PointSet<PointType> & points,
    const Scalar & preconditioningScale,
    const TranslationVector & preconditioningTranslation);

  void compute(
    const PointSet<PointType> & points,
    const PointSetPreconditionerType & preconditioner);

  void compute(
    const PointSet<PointType> & points,
    const Scalar & preconditioningScale);

  void compute(
    const PointSet<PointType> & points,
    const Scalar & preconditioningScale,
    const TranslationVector & preconditioningTranslation);


  const PointSet<PointType> & get()const;

  const TransformationMatrix & getPreconditioningMatrix() const;

private:
  void allocate_(const size_t & numberOfPoints);

private:
  PointSet<PointType> points_;
  TransformationMatrix preconditioningMatrix_;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__PRECONDITIONEDPOINTSET_HPP_
