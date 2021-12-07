#include "romea_core_common/regression/leastsquares/NLSE.hpp"

namespace {
const double DEFAULT_ALPHA = 0.7;
const double DEFAULT_ESTIMATE_EPSILON = 0.01;
}

namespace romea
{

//-----------------------------------------------------------------------------
template <typename RealType>
NLSE<RealType>::NLSE():
  NLSE(DEFAULT_ESTIMATE_EPSILON,DEFAULT_ALPHA)
{

}

//-----------------------------------------------------------------------------
template <typename RealType>
NLSE<RealType>::NLSE(const double &estimateEpsilon):
  NLSE(estimateEpsilon,DEFAULT_ALPHA)
{

}

//-----------------------------------------------------------------------------
template <typename RealType>
NLSE<RealType>::NLSE(const double &estimateEpsilon,const RealType & alpha):
  alpha_(alpha),
  estimate_(),
  estimateDelta_(),
  estimateCovariance_(),
  estimateEpsilon_(estimateEpsilon),
  numberOfIterations_(0),
  leastSquares_(),
  rmse_(-1)
{

}

//-----------------------------------------------------------------------------
template <typename RealType>
bool NLSE<RealType>::estimate(const size_t &maximalNumberOfIterations, const double &dataStd)
{

  computeGuess_();
  numberOfIterations_=0;
  rmse_ =-1;

  //estimate
  while(numberOfIterations_ < maximalNumberOfIterations)
  {
    computeJacobianAndY_();

    //    std::cout <<" J "<< std::endl;
    //    std::cout << J << std::endl;

    //    std::cout << "Y" << std::endl;
    //    std::cout << Y << std::endl;

    estimateDelta_ = RealType(0.7)*leastSquares_.estimateUsingSVD();

    //    std::cout << " D " << std::endl;
    //    std::cout <<  estimateDelta_.transpose() << std::endl;

    if(estimateDelta_.norm()<estimateEpsilon_)
    {
      break;
    }

    estimate_-=estimateDelta_;

    //    std::cout << " X " << std::endl;
    //    std::cout <<  estimate_.transpose() << std::endl;

    ++numberOfIterations_;
  }

  if(numberOfIterations_==maximalNumberOfIterations)
  {
    return false;
  }

  computeJacobianAndY_();

  double dataVar = dataStd*dataStd;
  double mse = leastSquares_.getY().norm()/leastSquares_.getY().rows();
  if(mse > 25* dataStd)
  {
    return false;
  }

  rmse_= std::sqrt(mse);
  estimateCovariance_=leastSquares_.computeEstimateCovariance(dataVar);
  return true;
}

//-----------------------------------------------------------------------------
template <typename RealType>
const size_t & NLSE<RealType>::getNumberOfIterations()
{
  return numberOfIterations_;
}

//-----------------------------------------------------------------------------
template <typename RealType>
const double & NLSE<RealType>::getRootMeanSquareError()
{
  return rmse_;
}

//-----------------------------------------------------------------------------
template <typename RealType>
const typename NLSE<RealType>::Vector & NLSE<RealType>::getEstimate()
{
  return estimate_;
}

//-----------------------------------------------------------------------------
template <typename RealType>
const typename NLSE<RealType>::Matrix & NLSE<RealType>::getEstimateCovariance()
{
  return estimateCovariance_;
}

template class NLSE<float>;
template class NLSE<double>;

}
