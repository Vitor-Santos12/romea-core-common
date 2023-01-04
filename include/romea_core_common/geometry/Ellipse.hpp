// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__ELLIPSE_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__ELLIPSE_HPP_

// Eigen
#include <Eigen/Core>

namespace romea
{

class Ellipse
{
public:
  Ellipse(
    const double & xCenter,
    const double & yCenter,
    const double & orientation,
    const double & majorRadius,
    const double & minorRadius);

  Ellipse(
    const Eigen::Vector2d & centerPosition,
    const double & orientation,
    const double & majorRadius,
    const double & minorRadius);

  Ellipse(
    const Eigen::Vector2d & centerPosition,
    const Eigen::Matrix2d & covarianceMatrix,
    const double & sigmaScale);

public:
  const Eigen::Vector2d & getCenterPosition()const;

  const double & getOrientation()const;

  const double & getMajorRadius()const;

  const double & getMinorRadius()const;

protected:
  Eigen::Vector2d centerPosition_;
  double orientation_;
  double majorRadius_;
  double minorRadius_;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


}  // namespace romea


#endif  // ROMEA_CORE_COMMON__GEOMETRY__ELLIPSE_HPP_
