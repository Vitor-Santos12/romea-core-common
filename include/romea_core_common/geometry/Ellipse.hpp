#ifndef romea_Ellipse_hpp
#define romea_Ellipse_hpp

//Eigen
#include "Eigen/Core"


namespace romea {

class Ellipse{
public :

  Ellipse(const double & xCenter,
          const double & yCenter,
          const double & orientation,
          const double & majorRadius,
          const double & minorRadius);
  
  Ellipse(const Eigen::Vector2d & centerPosition,
          const double & orientation,
          const double & majorRadius,
          const double & minorRadius);


  Ellipse(const Eigen::Vector2d &centerPosition,
          const Eigen::Matrix2d &covarianceMatrix,
          const double & sigmaScale);

public :

  const Eigen::Vector2d & getCenterPosition()const;

  const double & getOrientation()const;

  const double & getMajorRadius()const;

  const double & getMinorRadius()const;

protected :

  Eigen::Vector2d centerPosition_;
  double orientation_;
  double majorRadius_;
  double minorRadius_;

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};


}//romea


#endif
