//romea
#include "romea_common/regression/leastsquares/MEstimator.hpp"

//std
#include <algorithm>

namespace romea {

//----------------------------------------------------------------------------
template <typename RealType>
MEstimator<RealType>::MEstimator(RealType dataNoiseStd):
  dataSize_(0),
  dataNoiseStd_(dataNoiseStd),
  sortedVector_(),
  normalizedResiduals_(),
  weights_(),
  ones_()
{

}

//----------------------------------------------------------------------------
template <typename RealType> void
MEstimator<RealType>::allocate_(const int & dataSize)
{

  dataSize_ = dataSize;

  if(sortedVector_.rows()<dataSize)
  {
    sortedVector_.resize(dataSize_);
    normalizedResiduals_.resize(dataSize_);
    weights_.resize(dataSize_);
    ones_.resize(dataSize_);
    ones_.setConstant(RealType(1.0));
  }
}

//----------------------------------------------------------------------------
template <typename RealType> RealType
MEstimator<RealType>::computeWeights(const Vector & residuals)
{
  return computeWeights(residuals,0);
}

//----------------------------------------------------------------------------
template <typename RealType> RealType
MEstimator<RealType>::computeWeights(const Vector & residuals,
                                     const size_t &numberOfDiscardedData)
{

  assert(int(numberOfDiscardedData)<=residuals.rows());

  allocate_(static_cast<int>(residuals.rows()));
  int numberOfAvailableData = dataSize_ - int(numberOfDiscardedData);

  //Compute median
  sortedVector_.head(dataSize_).noalias() = residuals;
  RealType * itBegin  = sortedVector_.data();
  RealType * itMedian = itBegin + numberOfAvailableData/2;
  RealType * itEnd    = itBegin + dataSize_;
  std::nth_element(itBegin, itMedian, itEnd);

  //Compute MAD
  normalizedResiduals_.head(dataSize_).array() =(residuals.array()-(*itMedian)).abs();
  sortedVector_.head(dataSize_) = normalizedResiduals_.head(dataSize_);
  std::nth_element(itBegin, itMedian, itEnd);

  RealType mad = std::max(RealType(1.4826)*(*itMedian),dataNoiseStd_);

  // Huber weighting
  mad = RealType(1.2107) * mad;
  weights_.head(dataSize_).array() =
      (normalizedResiduals_.head(dataSize_).array()/mad).
      inverse().min(ones_.head(dataSize_).array());

  //apply weighting only when ratio inliers/outliers are up to 80 percent
  int numberOfInliers = (weights_.array() < ones_.head(dataSize_).array()).sum()-int(numberOfDiscardedData);
  return numberOfInliers/RealType(numberOfAvailableData);

}

template class MEstimator<float>;
template class MEstimator<double>;

}

