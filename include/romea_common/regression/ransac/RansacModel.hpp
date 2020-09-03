#ifndef romea_RansacModel_hpp
#define romea_RansacModel_hpp

//stl
#include <cstddef>

namespace romea {

//TODO perhaps use crtp here

class RansacModel{

public :

  RansacModel();

  virtual ~RansacModel()=default;

  virtual bool draw(const double &modelDeviationError)=0;

  virtual size_t countInliers(const double & modelDeviationError)=0;

  virtual void refine()=0;

  virtual size_t getNumberOfPoints() const =0;

  virtual size_t getNumberOfPointsToDrawModel() const =0;

  virtual size_t getMinimalNumberOfInliers() const =0;

  virtual double getRootMeanSquareError() const =0;

};

}

#endif
