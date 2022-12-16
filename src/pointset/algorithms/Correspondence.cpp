// romea
#include "romea_core_common/pointset/algorithms/Correspondence.hpp"

namespace romea {

//-----------------------------------------------------------------------------
Correspondence::Correspondence():
  Correspondence(0, 0, 0, 1)
{

}

//-----------------------------------------------------------------------------
Correspondence::Correspondence(const size_t &sourcePointIndex,
                               const size_t &targetPointIndex):
  Correspondence(sourcePointIndex, targetPointIndex, 0., 1)
{

}

//-----------------------------------------------------------------------------
Correspondence::Correspondence(const size_t &sourcePointIndex,
                               const size_t &targetPointIndex,
                               const double & squareDistanceBetweenPoints):
  Correspondence(sourcePointIndex, targetPointIndex, squareDistanceBetweenPoints, 1)

{

}

//-----------------------------------------------------------------------------
Correspondence::Correspondence(const size_t &sourcePointIndex_,
                               const size_t &targetPointIndex_,
                               const double &squareDistanceBetweenPoints_,
                               const double &weight_):
  sourcePointIndex(sourcePointIndex_),
  targetPointIndex(targetPointIndex_),
  squareDistanceBetweenPoints(squareDistanceBetweenPoints_),
  weight(weight_)
{
}

}   // namespace romea
