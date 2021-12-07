#ifndef romea_Ransac_hpp
#define romea_Ransac_hpp

#include "../../regression/ransac/RansacModel.hpp"

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


}
#endif
