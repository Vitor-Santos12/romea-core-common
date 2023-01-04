// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

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

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__TRANSFORM__ESTIMATION__FINDRIGIDTRANSFORMATIONBYLEASTSQUARES_HPP_
