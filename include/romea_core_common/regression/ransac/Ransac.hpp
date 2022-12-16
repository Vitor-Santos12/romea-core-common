#ifndef ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSAC_HPP_
#define ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSAC_HPP_

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

#endif  // ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSAC_HPP_
