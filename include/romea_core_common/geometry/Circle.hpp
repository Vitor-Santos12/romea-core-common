// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEOMETRY__CIRCLE_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__CIRCLE_HPP_

// Eigen
#include <Eigen/Core>

namespace romea {

class Circle {
public :

  Circle(const double & xCenter,
         const double & yCenter,
         const double & radius);

  Circle(const Eigen::Vector2d & centerPosition,
         const double & radius);

public :

  const Eigen::Vector2d & getCenterPosition()const;

  const double & getRadius()const;

protected :

  Eigen::Vector2d centerPosition_;
  double radius_;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};


}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__CIRCLE_HPP_
