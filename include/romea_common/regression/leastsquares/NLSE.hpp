#ifndef romea_NLSE_hpp
#define romea_NLSE_hpp

#include "LeastSquares.hpp"

namespace romea {

template <typename RealType>
class NLSE
{

public :


  using Vector = Eigen::Matrix<RealType,Eigen::Dynamic,1>;
  using Matrix = Eigen::Matrix<RealType,Eigen::Dynamic,Eigen::Dynamic>;

public :


  NLSE();

  NLSE(const double & estimateEpsilon);

  NLSE(const double & estimateEpsilon, const RealType & alpha);

  virtual ~NLSE()=default;

public :


  virtual bool estimate(const size_t & maximalNumberOfIterations,
                        const double & dataStd);

  const size_t &getNumberOfIterations();

  const double & getRootMeanSquareError();

  const Vector & getEstimate();

  const Matrix & getEstimateCovariance();

protected :

  virtual void computeGuess_()=0;

  virtual void computeJacobianAndY_()=0;

protected :


  double alpha_;
  Vector estimate_;
  Vector estimateDelta_;
  Matrix estimateCovariance_;
  double estimateEpsilon_;
  size_t numberOfIterations_;
  LeastSquares<RealType> leastSquares_;
  double rmse_;
};



}

#endif
