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
#include <limits>
#include <vector>

// romea
#include "romea_core_common/transform/estimation/FindRigidTransformationByICP.hpp"
#include "romea_core_common/pointset/algorithms/NormalAndCurvatureEstimation.hpp"

namespace
{
const size_t ICP_MAXIMAL_NUMBER_OF_ITERATIONS = 10;
const double ICP_TRANSFORMATION_EPSILON = 0.001;
}


namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
template<class PointType>
FindRigidTransformationByICP<PointType>::FindRigidTransformationByICP(
  const Scalar & pointsPositionStd)
: targetPointsNormals_(),
  projectedTargetPoints_(),
  correspondences_(),
  matchedSourcePoints_(),
  matchedTargetPoints_(),
  matchedTargetNormals_(),
  matchedCorrespondences_(),
  ransacModel_(),
  ransac_(&ransacModel_, pointsPositionStd),
  maximalNumberOfIterations_(ICP_MAXIMAL_NUMBER_OF_ITERATIONS),
  transformationEpsilon_(ICP_TRANSFORMATION_EPSILON)
{
}


//-----------------------------------------------------------------------------
template<class PointType>
void
FindRigidTransformationByICP<PointType>::setMaximalNumberOfIterations(
  const size_t & numberOfIterations)
{
  maximalNumberOfIterations_ = numberOfIterations;
}


//-----------------------------------------------------------------------------
template<class PointType>
void
FindRigidTransformationByICP<PointType>::setTransformationEspilon(const Scalar & epsilon)
{
  transformationEpsilon_ = epsilon;
}


//-----------------------------------------------------------------------------
template<class PointType>
void FindRigidTransformationByICP<PointType>::allocate_(size_t numberOfPoints)
{
  if (matchedTargetPoints_.capacity() < numberOfPoints) {
    targetPointsNormals_.reserve(numberOfPoints);
    projectedTargetPoints_.reserve(numberOfPoints);
    correspondences_.reserve(numberOfPoints);
    matchedSourcePoints_.reserve(numberOfPoints);
    matchedTargetPoints_.reserve(numberOfPoints);
    matchedTargetNormals_.reserve(numberOfPoints);
    correspondences_.reserve(numberOfPoints);
    matchedCorrespondences_.reserve(numberOfPoints);
  }
}

//-----------------------------------------------------------------------------
template<class PointType>
bool FindRigidTransformationByICP<PointType>::find(
  const PointSet<PointType> & sourcePoints,
  const PointSet<PointType> & targetPoints,
  const TransformationMatrixType & guessRigidTransformation,
  EstimationMethod estimationMethod)
{
  KdTreeType sourcePointsKdTree(sourcePoints);
  KdTreeType targetPointsKdTree(targetPoints);

  return find(
    sourcePoints, sourcePointsKdTree,
    targetPoints, targetPointsKdTree,
    guessRigidTransformation,
    estimationMethod);
}

// TODO(jean) a factoriser
//-----------------------------------------------------------------------------
template<class PointType>
bool FindRigidTransformationByICP<PointType>::find(
  const PointSet<PointType> & sourcePoints,
  const KdTreeType & sourcePointsKdTree,
  const PointSet<PointType> & targetPoints,
  const KdTreeType & targetPointsKdTree,
  const TransformationMatrixType & guessRigidTransformation,
  EstimationMethod estimationMethod)
{
  size_t numberOfTargetPoints = targetPoints.size();
  allocate_(numberOfTargetPoints);

  // Normal estimation of target points set
  NormalAndCurvatureEstimation<PointType> normalEstimation(10);
  targetPointsNormals_.resize(numberOfTargetPoints, PointType::Zero());
  normalEstimation.compute(targetPoints, targetPointsKdTree, targetPointsNormals_);

  // Try to estimate the rigid transformation
  double bestFittingRMSE = std::numeric_limits<double>::max();
  TransformationMatrixType bestRigidTransformation = TransformationMatrixType::Identity();
  TransformationMatrixType previousEstimatedTransformation = TransformationMatrixType::Identity();

  size_t n = 0;
  for (; n < maximalNumberOfIterations_; ++n) {
    // Project target points in source point references frame
    projectedTargetPoints_.resize(numberOfTargetPoints);
    TransformationMatrixType bestInverseRigidTransformation =
      (bestRigidTransformation * guessRigidTransformation).inverse();

    for (size_t targetIndex = 0; targetIndex < numberOfTargetPoints; ++targetIndex) {
      projection(
        bestInverseRigidTransformation,
        targetPoints[targetIndex],
        projectedTargetPoints_[targetIndex]);
    }

    // Search for each target point a nearest source point;
    size_t sourceIndex;
    Scalar nearestNeighborSquareDistance;

    correspondences_.clear();
    assert(correspondences_.capacity() >= numberOfTargetPoints);
    for (size_t targetIndex = 0; targetIndex < numberOfTargetPoints; ++targetIndex) {
      sourcePointsKdTree.findNearestNeighbor(
        projectedTargetPoints_[targetIndex],
        sourceIndex, nearestNeighborSquareDistance);

      correspondences_.emplace_back(sourceIndex, targetIndex, nearestNeighborSquareDistance);
    }

    // Remove wrong correspondences
    std::vector<Correspondence>::iterator itEnd;
    std::sort(
      std::begin(correspondences_),
      std::end(correspondences_),
      sortBySourceIndexAndDistancePredicate);

    itEnd = std::unique(
      std::begin(correspondences_),
      std::end(correspondences_),
      equalSourceIndexesPredicate);


    // Create matched point sets
    size_t numberOfMatchedPoints = static_cast<size_t>(
      std::distance(std::begin(correspondences_), itEnd));
    matchedSourcePoints_.resize(numberOfMatchedPoints);
    matchedTargetPoints_.resize(numberOfMatchedPoints);
    matchedTargetNormals_.resize(numberOfMatchedPoints);
    matchedCorrespondences_.resize(numberOfMatchedPoints);

    for (size_t n = 0; n < numberOfMatchedPoints; ++n) {
      const Correspondence & correspondence = correspondences_[n];
      //      matchedSourcePoints_[n]=guessRigidTransformation*sourcePoints[correspondence.sourcePointIndex];
      matchedTargetPoints_[n] = targetPoints[correspondence.targetPointIndex];
      matchedTargetNormals_[n] = targetPointsNormals_[correspondence.targetPointIndex];

      projection(
        guessRigidTransformation,
        sourcePoints[correspondence.sourcePointIndex], matchedSourcePoints_[n]);

      matchedCorrespondences_[n].sourcePointIndex = n;
      matchedCorrespondences_[n].targetPointIndex = n;
    }

    // Load data in ransac consensus
    ransacModel_.loadPointSets(&matchedSourcePoints_, &matchedTargetPoints_);
    ransacModel_.loadCorrespondences(&matchedCorrespondences_, numberOfMatchedPoints);

    switch (estimationMethod) {
      case EstimationMethod::LEAST_SQUARES:
        ransacModel_.loadTargetNormalSet(&matchedTargetNormals_);
        break;
      case EstimationMethod::SVD:
        ransacModel_.loadTargetNormalSet(nullptr);
        break;
    }

    // Estimate transformation
    if (ransac_.estimateModel()) {
      // Difference between consecutive estimated tranformations
      Scalar differenceBetweenTransformations =
        (ransacModel_.getTransformation() -
        previousEstimatedTransformation).array().abs().sum();

      // Backup best estimate
      if (ransacModel_.getRootMeanSquareError() < bestFittingRMSE) {
        bestRigidTransformation = ransacModel_.getTransformation();
        bestFittingRMSE = ransacModel_.getRootMeanSquareError();
      }

      // Break loop ?
      if (differenceBetweenTransformations < transformationEpsilon_) {
        break;
      }

      // Backup current estimation
      previousEstimatedTransformation = ransacModel_.getTransformation();
    }
  }

  return n != maximalNumberOfIterations_;
}

//-----------------------------------------------------------------------------
template<class PointType>
const typename FindRigidTransformationByICP<PointType>::TransformationMatrixType &
FindRigidTransformationByICP<PointType>::getTransformation()const
{
  return ransacModel_.getTransformation();
}

template class FindRigidTransformationByICP<Eigen::Vector2f>;
template class FindRigidTransformationByICP<Eigen::Vector2d>;
template class FindRigidTransformationByICP<Eigen::Vector3f>;
template class FindRigidTransformationByICP<Eigen::Vector3d>;

template class FindRigidTransformationByICP<HomogeneousCoordinates2f>;
template class FindRigidTransformationByICP<HomogeneousCoordinates2d>;
template class FindRigidTransformationByICP<HomogeneousCoordinates3f>;
template class FindRigidTransformationByICP<HomogeneousCoordinates3d>;

}  // namespace core
}  // namespace romea
