// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__MATH__TRANSFORMATION_HPP_
#define ROMEA_CORE_COMMON__MATH__TRANSFORMATION_HPP_

// Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace romea
{

//-----------------------------------------------------------------------------
template<typename Scalar>
inline Eigen::Transform<Scalar, 3, Eigen::Affine> rigid_transformation3(
  const Eigen::Matrix<Scalar, 3, 1> & translation,
  const Eigen::Matrix<Scalar, 3, 1> & angles)
{
  using EigenVector = Eigen::Matrix<Scalar, 3, 1>;
  using EigenAngleAxis = Eigen::AngleAxis<Scalar>;
  using EigenTransform = Eigen::Transform<Scalar, 3, Eigen::Affine>;

  EigenTransform rigidTransformation = EigenTransform::Identity();
  rigidTransformation.rotate(EigenAngleAxis(angles[0], EigenVector::UnitX()));
  rigidTransformation.rotate(EigenAngleAxis(angles[1], EigenVector::UnitY()));
  rigidTransformation.rotate(EigenAngleAxis(angles[2], EigenVector::UnitZ()));
  rigidTransformation.translate(translation);
  return rigidTransformation;
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__MATH__TRANSFORMATION_HPP_
