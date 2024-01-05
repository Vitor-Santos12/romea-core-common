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


// romea
#include "romea_core_common/pointset/algorithms/PreconditionedPointSet.hpp"

namespace romea
{
namespace core
{


//-----------------------------------------------------------------------------
template<class PointType>
PreconditionedPointSet<PointType>::PreconditionedPointSet()
: points_(),
  preconditioningMatrix_(TransformationMatrix::Identity())
{
}

//-----------------------------------------------------------------------------
template<class PointType>
PreconditionedPointSet<PointType>::PreconditionedPointSet(
  const PointSet<PointType> & points,
  const PointSetPreconditionerType & preconditioner)
: PreconditionedPointSet<PointType>::PreconditionedPointSet()
{
  compute(points, preconditioner);
}

//-----------------------------------------------------------------------------
template<class PointType>
PreconditionedPointSet<PointType>::PreconditionedPointSet(
  const PointSet<PointType> & points,
  const Scalar & preconditioningScale)
: PreconditionedPointSet<PointType>::PreconditionedPointSet()
{
  compute(points, preconditioningScale);
}

//-----------------------------------------------------------------------------
template<class PointType>
PreconditionedPointSet<PointType>::PreconditionedPointSet(
  const PointSet<PointType> & points,
  const Scalar & preconditioningScale,
  const TranslationVector & preconditioningTranslation)
: PreconditionedPointSet<PointType>::PreconditionedPointSet()
{
  compute(points, preconditioningScale, preconditioningTranslation);
}


//-----------------------------------------------------------------------------
template<class PointType>
void
PreconditionedPointSet<PointType>::compute(
  const PointSet<PointType> & points,
  const PointSetPreconditionerType & preconditioner)
{
  compute(points, preconditioner.getScale(), preconditioner.getTranslation());
}

//-----------------------------------------------------------------------------
template<class PointType>
void
PreconditionedPointSet<PointType>::compute(
  const PointSet<PointType> & points,
  const Scalar & preconditioningScale)
{
  // Reallocate point set
  size_t numberOfPoints = points.size();
  allocate_(points.size());

  // point preconditioning
  Eigen::Array<Scalar, POINT_SIZE, 1> scale = Eigen::Array<Scalar, POINT_SIZE, 1>::Ones();
  scale.head(CARTESIAN_DIM) *= preconditioningScale;

  for (size_t n = 0; n < numberOfPoints; ++n) {
    points_[n].array() = points[n].array() * preconditioningScale;
  }

  // Backup preconditiond parameters
  preconditioningMatrix_ = TransformationMatrix::Identity();
  preconditioningMatrix_.block(0, 0, CARTESIAN_DIM, CARTESIAN_DIM) *= preconditioningScale;
}

//-----------------------------------------------------------------------------
template<class PointType>
void
PreconditionedPointSet<PointType>::compute(
  const PointSet<PointType> & points,
  const Scalar & preconditioningScale,
  const TranslationVector & preconditioningTranslation)
{
  // Reallocate point set
  size_t numberOfPoints = points.size();
  allocate_(points.size());

  // point preconditioning
  Eigen::Array<Scalar, POINT_SIZE, 1> scale = Eigen::Array<Scalar, POINT_SIZE, 1>::Ones();
  Eigen::Array<Scalar, POINT_SIZE, 1> translation = Eigen::Array<Scalar, POINT_SIZE, 1>::Zero();
  scale.head(CARTESIAN_DIM) *= preconditioningScale;
  translation.head(CARTESIAN_DIM) = preconditioningTranslation;

  for (size_t n = 0; n < numberOfPoints; ++n) {
    points_[n].array() = scale * points[n].array() + translation;
  }

  // Compute preconditioning matrix
  preconditioningMatrix_ = TransformationMatrix::Identity();
  preconditioningMatrix_.block(0, 0, CARTESIAN_DIM, CARTESIAN_DIM) *= preconditioningScale;
  preconditioningMatrix_.block(0, CARTESIAN_DIM, CARTESIAN_DIM, 1) = preconditioningTranslation;
}

//-----------------------------------------------------------------------------
template<class PointType>
void
PreconditionedPointSet<PointType>::allocate_(const size_t & numberOfPoints)
{
  if (points_.capacity() < numberOfPoints) {
    points_.reserve(numberOfPoints);
  }

  points_.resize(numberOfPoints);
}

//-----------------------------------------------------------------------------
template<class PointType>
const PointSet<PointType> & PreconditionedPointSet<PointType>::get()const
{
  return points_;
}

//-----------------------------------------------------------------------------
template<class PointType>
const typename PreconditionedPointSet<PointType>::TransformationMatrix &
PreconditionedPointSet<PointType>::getPreconditioningMatrix()const
{
  return preconditioningMatrix_;
}

template class PreconditionedPointSet<Eigen::Vector2f>;
template class PreconditionedPointSet<Eigen::Vector2d>;
template class PreconditionedPointSet<Eigen::Vector3f>;
template class PreconditionedPointSet<Eigen::Vector3d>;

template class PreconditionedPointSet<HomogeneousCoordinates2f>;
template class PreconditionedPointSet<HomogeneousCoordinates2d>;
template class PreconditionedPointSet<HomogeneousCoordinates3f>;
template class PreconditionedPointSet<HomogeneousCoordinates3d>;

}   // namespace core
}   // namespace romea
