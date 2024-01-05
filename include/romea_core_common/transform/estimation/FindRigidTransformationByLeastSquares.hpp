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


#ifndef ROMEA_CORE_COMMON__TRANSFORM__ESTIMATION__FINDRIGIDTRANSFORMATIONBYLEASTSQUARES_HPP_
#define ROMEA_CORE_COMMON__TRANSFORM__ESTIMATION__FINDRIGIDTRANSFORMATIONBYLEASTSQUARES_HPP_

// std
#include <vector>

// romea
#include "romea_core_common/coordinates/CartesianCoordinates.hpp"
#include "romea_core_common/coordinates/HomogeneousCoordinates.hpp"
#include "romea_core_common/regression/leastsquares/LeastSquares.hpp"
#include "romea_core_common/pointset/algorithms/PreconditionedPointSet.hpp"
#include "romea_core_common/pointset/algorithms/Correspondence.hpp"
#include "romea_core_common/pointset/NormalSet.hpp"

namespace romea
{
namespace core
{

template<class PointType>
class FindRigidTransformationByLeastSquares
{
public:
  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using PreconditionedPointSetType = PreconditionedPointSet<PointType>;
  using TransformationMatrixType = Eigen::Matrix<Scalar, CARTESIAN_DIM + 1, CARTESIAN_DIM + 1>;

public:
  FindRigidTransformationByLeastSquares();

  TransformationMatrixType find(
    const PointSet<PointType> & sourcePoints,
    const PointSet<PointType> & targetPoints,
    const NormalSet<PointType> & targetPointsNormals);

  TransformationMatrixType find(
    const PreconditionedPointSetType & sourcePoints,
    const PreconditionedPointSetType & targetPoints,
    const NormalSet<PointType> & targetPointsNormals);


  TransformationMatrixType find(
    const PointSet<PointType> & sourcePoints,
    const PointSet<PointType> & targetPoints,
    const NormalSet<PointType> & targetPointsNormals,
    const std::vector<Correspondence> & correspondences);

  TransformationMatrixType find(
    const PreconditionedPointSetType & sourcePoints,
    const PreconditionedPointSetType & targetPoints,
    const NormalSet<PointType> & targetPointsNormals,
    const std::vector<Correspondence> & correspondences);

  void setPreconditioner(
    const PreconditionedPointSetType & sourcePoints,
    const PreconditionedPointSetType & targetPoints);

private:
  TransformationMatrixType estimate_(
    const PointSet<PointType> & sourcePoints,
    const PointSet<PointType> & targetPoints,
    const NormalSet<PointType> & targetPointsNormals);

  TransformationMatrixType estimate_(
    const PointSet<PointType> & sourcePoints,
    const PointSet<PointType> & targetPoints,
    const NormalSet<PointType> & targetPointsNormals,
    const std::vector<Correspondence> & correspondences);

private:
  LeastSquares<Scalar> leastSquares_;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__TRANSFORM__ESTIMATION__FINDRIGIDTRANSFORMATIONBYLEASTSQUARES_HPP_
