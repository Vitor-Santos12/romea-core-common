#ifndef ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACMODEL_HPP_
#define ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACMODEL_HPP_

// stl
#include <cstddef>

namespace romea {

// TODO(jean) perhaps use crtp here

class RansacModel
{
public :

  RansacModel();

  virtual ~RansacModel() = default;

  virtual bool draw(const double &modelDeviationError) = 0;

  virtual size_t countInliers(const double & modelDeviationError) = 0;

  virtual void refine() = 0;

  virtual size_t getNumberOfPoints() const = 0;

  virtual size_t getNumberOfPointsToDrawModel() const = 0;

  virtual size_t getMinimalNumberOfInliers() const = 0;

  virtual double getRootMeanSquareError() const = 0;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACMODEL_HPP_
