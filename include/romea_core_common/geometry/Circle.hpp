#ifndef romea_Circle_hpp
#define romea_Circle_hpp

//Eigen
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


}//romea

#endif
