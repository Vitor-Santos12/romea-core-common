#ifndef __OnlineVariance_H__
#define __OnlineVariance_H__

#include "OnlineAverage.hpp"

namespace romea {

class OnlineVariance : public OnlineAverage
{

public :


  OnlineVariance(const double & averagePrecision,size_t windowSize);

  OnlineVariance(const double & averagePrecision);

  OnlineVariance(const OnlineVariance & onlineVariance);

  virtual ~OnlineVariance()=default;

public :

  virtual void setWindowSize(const size_t & windowSize) override;

  virtual void update(const double &value) override;

  virtual void reset() override;

  double getVariance()const;

private :

  size_t windowSizeMinusOne_;
  int squaredMultiplier_;

  std::vector<long long int> squaredData_;
  long long int sumOfSquaredData_;
  double variance_;

};

}

#endif
