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


// std
#include <vector>

// romea
#include "romea_core_common/transform/estimation/FindRigidTransformationBySVD.hpp"
#include "romea_core_common/containers/Eigen/EigenContainers.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
template<class PointType>
FindRigidTransformationBySVD<PointType>::FindRigidTransformationBySVD()
{
}

//-----------------------------------------------------------------------------
template<class PointType>
typename FindRigidTransformationBySVD<PointType>::TransformationMatrixType
FindRigidTransformationBySVD<PointType>::find(
  const PreconditionedPointSetType & sourcePoints,
  const PreconditionedPointSetType & targetPoints,
  const std::vector<Correspondence> & correspondences)
{
  TransformationMatrixType H = estimate_(sourcePoints.get(), targetPoints.get(), correspondences);
  H.block(0, CARTESIAN_DIM, CARTESIAN_DIM, 1) /= targetPoints.getPreconditioningMatrix()(0, 0);
  return H;
}

//-----------------------------------------------------------------------------
template<class PointType>
typename FindRigidTransformationBySVD<PointType>::TransformationMatrixType
FindRigidTransformationBySVD<PointType>::find(
  const PointSet<PointType> & sourcePoints,
  const PointSet<PointType> & targetPoints,
  const std::vector<Correspondence> & correspondences)
{
  return estimate_(sourcePoints, targetPoints, correspondences);
}

//-----------------------------------------------------------------------------
template<class PointType>
typename FindRigidTransformationBySVD<PointType>::TransformationMatrixType
FindRigidTransformationBySVD<PointType>::find(
  const PreconditionedPointSetType & sourcePoints,
  const PreconditionedPointSetType & targetPoints)
{
  TransformationMatrixType H = estimate_(sourcePoints.get(), targetPoints.get());
  H.block(0, CARTESIAN_DIM, CARTESIAN_DIM, 1) /= targetPoints.getPreconditioningMatrix()(0, 0);
  return H;
}

//-----------------------------------------------------------------------------
template<class PointType>
typename FindRigidTransformationBySVD<PointType>::TransformationMatrixType
FindRigidTransformationBySVD<PointType>::find(
  const PointSet<PointType> & sourcePoints,
  const PointSet<PointType> & targetPoints)
{
  return estimate_(sourcePoints, targetPoints);
}


//-----------------------------------------------------------------------------
template<class PointType>
typename FindRigidTransformationBySVD<PointType>::TransformationMatrixType
FindRigidTransformationBySVD<PointType>::estimate_(
  const PointSet<PointType> & sourcePoints,
  const PointSet<PointType> & targetPoints,
  const std::vector<Correspondence> & correspondences)
{
  // TODO(jean)  changer un calcul single pass
  // Compute mean
  PointType sourceMean = PointType::Zero();
  PointType targetMean = PointType::Zero();
  for (size_t n = 0, N = correspondences.size(); n < N; ++n) {
    const size_t & sourceIndex = correspondences[n].sourcePointIndex;
    const size_t & targetIndex = correspondences[n].targetPointIndex;
    sourceMean += sourcePoints[sourceIndex];
    targetMean += targetPoints[targetIndex];
  }
  sourceMean /= Scalar(correspondences.size());
  targetMean /= Scalar(correspondences.size());

  // Compute covariance
  Eigen::Matrix<Scalar, POINT_SIZE, POINT_SIZE> cov =
    Eigen::Matrix<Scalar, POINT_SIZE, POINT_SIZE>::Zero();

  for (size_t n = 0; n < correspondences.size(); ++n) {
    const size_t & sourceIndex = correspondences[n].sourcePointIndex;
    const size_t & targetIndex = correspondences[n].targetPointIndex;
    cov += (sourcePoints[sourceIndex] - sourceMean) *
      (targetPoints[targetIndex] - targetMean).transpose();
  }

  Eigen::JacobiSVD<Eigen::Matrix<Scalar, -1, -1>>
  svd(cov.block(0, 0, CARTESIAN_DIM, CARTESIAN_DIM), Eigen::ComputeThinU | Eigen::ComputeThinV);

  Eigen::Matrix<Scalar, -1, -1> u = svd.matrixU();
  Eigen::Matrix<Scalar, -1, -1> v = svd.matrixV();

  //      if (u.determinant () * v.determinant () < 0)
  //      {
  //        for (int x = 0; x < d; ++x)
  //          v (x, d) *= -1;
  //      }

  // Compute translation
  TransformationMatrixType H = TransformationMatrixType::Identity();
  H.block(0, 0, CARTESIAN_DIM, CARTESIAN_DIM) = v * u.transpose();
  H.block(0, CARTESIAN_DIM, POINT_SIZE, 1) += targetMean -
    H.block(0, 0, POINT_SIZE, POINT_SIZE) * sourceMean;
  return H;
}

//-----------------------------------------------------------------------------
template<class PointType>
typename FindRigidTransformationBySVD<PointType>::TransformationMatrixType
FindRigidTransformationBySVD<PointType>::estimate_(
  const PointSet<PointType> & sourcePoints,
  const PointSet<PointType> & targetPoints)
{
  assert(sourcePoints.size() == targetPoints.size());

  // TODO(jean)  changer un calcul single pass

  // Compute mean
  PointType sourceMean = mean(sourcePoints);
  PointType targetMean = mean(targetPoints);

  // Compute covariance
  Eigen::Matrix<Scalar, POINT_SIZE, POINT_SIZE> cov =
    Eigen::Matrix<Scalar, POINT_SIZE, POINT_SIZE>::Zero();

  for (size_t n = 0; n < sourcePoints.size(); ++n) {
    cov += (sourcePoints[n] - sourceMean) *
      (targetPoints[n] - targetMean).transpose();
  }

  Eigen::JacobiSVD<Eigen::Matrix<Scalar, -1, -1>>
  svd(cov.block(0, 0, CARTESIAN_DIM, CARTESIAN_DIM), Eigen::ComputeThinU | Eigen::ComputeThinV);

  Eigen::Matrix<Scalar, -1, -1> u = svd.matrixU();
  Eigen::Matrix<Scalar, -1, -1> v = svd.matrixV();

  //      if (u.determinant () * v.determinant () < 0)
  //      {
  //        for (int x = 0; x < d; ++x)
  //          v (x, d) *= -1;
  //      }

  // Compute translation
  TransformationMatrixType H = TransformationMatrixType::Identity();
  H.block(0, 0, CARTESIAN_DIM, CARTESIAN_DIM) = v * u.transpose();
  H.block(0, CARTESIAN_DIM, POINT_SIZE, 1) += targetMean -
    H.block(0, 0, POINT_SIZE, POINT_SIZE) * sourceMean;
  return H;
}

template class FindRigidTransformationBySVD<Eigen::Vector2f>;
template class FindRigidTransformationBySVD<Eigen::Vector2d>;
template class FindRigidTransformationBySVD<Eigen::Vector3f>;
template class FindRigidTransformationBySVD<Eigen::Vector3d>;

template class FindRigidTransformationBySVD<HomogeneousCoordinates2f>;
template class FindRigidTransformationBySVD<HomogeneousCoordinates2d>;
template class FindRigidTransformationBySVD<HomogeneousCoordinates3f>;
template class FindRigidTransformationBySVD<HomogeneousCoordinates3d>;

}   // namespace core
}   // namespace romea
