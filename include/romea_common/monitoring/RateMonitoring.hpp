#ifndef _romea_RateMonitoring_hpp_
#define _romea_RateMonitoring_hpp_

//romea
#include "../time/Time.hpp"
#include "../concurrency/SharedVariable.hpp"

//std
#include <queue>
#include <atomic>

namespace romea {


class RateMonitoring
{
 public:

  RateMonitoring();

  RateMonitoring(const double & expectedRate);

  RateMonitoring(const RateMonitoring & RateMonitoring);

  void initialize(const double & expectedRate);

  double update(const Duration & duration);

  double getRate()const;

  bool timeout(const Duration & duration)const;

 private :

  size_t windowSize_;

  Duration lastPeriod_;
  SharedVariable<Duration> lastDuration_;
  std::queue<long long int> periods_;
  long long int periodsSum_;
  std::atomic<double> rate_;

};


}

#endif
