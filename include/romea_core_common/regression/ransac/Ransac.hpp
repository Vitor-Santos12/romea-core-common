// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSAC_HPP_
#define ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSAC_HPP_

#include "romea_core_common/regression/ransac/RansacModel.hpp"

namespace romea {

class Ransac{
public :

  Ransac(RansacModel * ransacModel,
         double modelErrorDeviation);

  bool estimateModel();

private :

  double fittingProbability_;
  double modelErrorDeviation_;
  int maximalNumberOfIterations_;

  RansacModel * ransacModel_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__REGRESSION__RANSAC__RANSAC_HPP_
