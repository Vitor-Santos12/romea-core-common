#ifndef ROMEA_CORE_COMMON_TRANSFORM_ESTIMATION_FINDRIGIDTRANSFORMATIONBYICP_HPP_
#define ROMEA_CORE_COMMON_TRANSFORM_ESTIMATION_FINDRIGIDTRANSFORMATIONBYICP_HPP_

// vector
#include <vector>

// romea
#include "romea_core_common/transform/estimation/RansacRigidTransformationModel.hpp"
#include "romea_core_common/regression/ransac/Ransac.hpp"
#include "romea_core_common/pointset/KdTree.hpp"


namespace romea
{

template <class PointType>
class FindRigidTransformationByICP
{
public :

  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using KdTreeType = KdTree<PointType> ;
  using TransformationMatrixType = Eigen::Matrix<Scalar, CARTESIAN_DIM +1, CARTESIAN_DIM +1>;

public :

  enum class EstimationMethod
  {
    LEAST_SQUARES = 0,
    SVD
  };

public :

  explicit FindRigidTransformationByICP(const Scalar & pointsPositionStd);

public :

  void setMaximalNumberOfIterations(const size_t & numberOfIterations);

  void setTransformationEspilon(const Scalar & epsilon);

public :


  bool find(const PointSet<PointType> & sourcePoints,
            const PointSet<PointType> & targetPoints,
            const TransformationMatrixType & guessTransformation,
            EstimationMethod estimationMethod = EstimationMethod::LEAST_SQUARES);

  bool find(const PointSet<PointType> & sourcePoints,
            const KdTreeType & sourcePointsKdTree,
            const PointSet<PointType> & targetPoints,
            const KdTreeType & targetPointsKdTree,
            const TransformationMatrixType & guessTransformation,
            EstimationMethod estimationMethod = EstimationMethod::LEAST_SQUARES);

  const TransformationMatrixType & getTransformation()const;

protected :

  void allocate_(size_t numberOfPoints);

protected :

  PointSet<PointType> targetPointsNormals_;
  PointSet<PointType> projectedTargetPoints_;
  std::vector<Correspondence> correspondences_;

  PointSet<PointType> matchedSourcePoints_;
  PointSet<PointType> matchedTargetPoints_;
  NormalSet<PointType> matchedTargetNormals_;
  std::vector<Correspondence> matchedCorrespondences_;

  RansacRigidTransformationModel<PointType> ransacModel_;
  Ransac ransac_;

  size_t maximalNumberOfIterations_;
  Scalar transformationEpsilon_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_TRANSFORM_ESTIMATION_FINDRIGIDTRANSFORMATIONBYICP_HPP_
