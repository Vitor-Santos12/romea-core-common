// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__POINTSETPRECONDITIONER_HPP_
#define ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__POINTSETPRECONDITIONER_HPP_

// Eigen
#include <unsupported/Eigen/MatrixFunctions>

// romea
#include "romea_core_common/pointset/PointSet.hpp"
#include "romea_core_common/pointset/PointTraits.hpp"

namespace romea
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

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__ALGORITHMS__POINTSETPRECONDITIONER_HPP_
