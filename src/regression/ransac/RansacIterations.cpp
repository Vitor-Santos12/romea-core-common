// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include "romea_core_common/regression/ransac/RansacIterations.hpp"

// stl
#include <cmath>
#include <algorithm>
#include <limits>

namespace
{
const double EPSILON = std::numeric_limits<double>::epsilon();
}

namespace romea
{

//-----------------------------------------------------------------------------
RansacIterations::RansacIterations(
  const size_t & numberOfPoints,
  const float & fittingProbability,
  const size_t & maximalNumberOfIterations)
: logOfFittingOppositeProbability_(std::log(1.0 - fittingProbability)),
  oneOverNumberOfPoints_(1.0 / double(numberOfPoints)),
  numberOfIterations_(maximalNumberOfIterations)
{

}

//-----------------------------------------------------------------------------
void RansacIterations::update(
  const size_t & numberOfInliers,
  const size_t & numberOfPointsToDrawModel)
{
  double outliersPercentage = double(numberOfInliers) * oneOverNumberOfPoints_;
  double outliersProbability = 1.0 -
    std::pow(outliersPercentage, double(numberOfPointsToDrawModel));
  outliersProbability = std::max(EPSILON, outliersProbability);       // Avoid division by -Inf
  outliersProbability = std::min(1.0 - EPSILON, outliersProbability); // Avoid division by 0.
  size_t numberOfIterations = logOfFittingOppositeProbability_ / std::log(outliersProbability);
  numberOfIterations_ = std::min(numberOfIterations_, double(numberOfIterations));
}

//-----------------------------------------------------------------------------
double RansacIterations::get() const
{
  return numberOfIterations_;
}

}  // namespace romea
