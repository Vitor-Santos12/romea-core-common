//romea
#include "romea_core_common/geometry/Circle.hpp"

namespace romea {


//-----------------------------------------------------------------------------
Circle::Circle(const double & xCenter,
               const double & yCenter,
               const double & radius):
  centerPosition_(Eigen::Vector2d(xCenter, yCenter)),
  radius_(radius)
{
}

//-----------------------------------------------------------------------------
Circle::Circle(const Eigen::Vector2d & centerPosition,
               const double & radius):
  centerPosition_(centerPosition),
  radius_(radius)
{
}



//-----------------------------------------------------------------------------
const Eigen::Vector2d & Circle::getCenterPosition()const
{
  return centerPosition_;
}

//-----------------------------------------------------------------------------
const double & Circle::getRadius()const
{
  return radius_;
}

}  // namespace romea
