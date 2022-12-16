#ifndef ROMEA_CORE_COMMON_REGRESSION_LEASTSQUARES_MESTIMATOR_HPP_
#define ROMEA_CORE_COMMON_REGRESSION_LEASTSQUARES_MESTIMATOR_HPP_

// std
#include <limits>

// Eigen
#include <Eigen/Eigen>

namespace romea{

const float MESTIMATOR_DISCARDED_VALUE_FLOAT = std::numeric_limits<float>::max();
const double MESTIMATOR_DISCARDED_VALUE_DOUBLE = std::numeric_limits<double>::max();

template<class RealType>
class MEstimator
{
public:
  using Vector = Eigen::Matrix<RealType, Eigen::Dynamic, 1>;

  explicit MEstimator(RealType dataNoiseStd);

  RealType computeWeights(const Vector & residuals);

  RealType computeWeights(const Vector & residualsWithDiscardedValue,
                          const size_t &numberOfDiscardedData);

  const Vector & getWeights()const;

private :

  void allocate_(const int & dataSize);

private :

  int dataSize_;
  RealType dataNoiseStd_;
  Vector sortedVector_;
  Vector normalizedResiduals_;
  Vector weights_;
  Vector ones_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_REGRESSION_LEASTSQUARES_MESTIMATOR_HPP_
