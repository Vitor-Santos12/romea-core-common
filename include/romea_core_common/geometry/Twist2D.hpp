#ifndef ROMEA_CORE_COMMON__GEOMETRY__TWIST2D_HPP_
#define ROMEA_CORE_COMMON__GEOMETRY__TWIST2D_HPP_

// Eigen
#include <Eigen/Core>

namespace romea
{

struct Twist2D
{
  Twist2D();

  double angularSpeed;
  Eigen::Vector2d linearSpeeds;
  Eigen::Matrix3d covariance;
};

std::ostream & operator<<(std::ostream & os, const Twist2D & twist2D);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEOMETRY__TWIST2D_HPP_
