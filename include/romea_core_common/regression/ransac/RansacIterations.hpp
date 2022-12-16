#ifndef ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACITERATIONS_HPP_
#define ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACITERATIONS_HPP_

// std
#include <cstddef>

namespace romea {

class RansacIterations
{
public :

  RansacIterations(const size_t & numberOfPoints,
                   const float & fittingProbability,
                   const size_t & maximalNumberOfIterations);

  void update(const size_t & numberOfInliers,
              const size_t & numberOfPointsToDrawModel);

  double get() const;

private :

  double logOfFittingOppositeProbability_;
  double oneOverNumberOfPoints_;
  double numberOfIterations_;
};

}

#endif  // ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACITERATIONS_HPP_
