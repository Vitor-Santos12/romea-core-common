// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACITERATIONS_HPP_
#define ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACITERATIONS_HPP_

// std
#include <cstddef>

namespace romea
{

class RansacIterations
{
public:
  RansacIterations(
    const size_t & numberOfPoints,
    const float & fittingProbability,
    const size_t & maximalNumberOfIterations);

  void update(
    const size_t & numberOfInliers,
    const size_t & numberOfPointsToDrawModel);

  double get() const;

private:
  double logOfFittingOppositeProbability_;
  double oneOverNumberOfPoints_;
  double numberOfIterations_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSACITERATIONS_HPP_
