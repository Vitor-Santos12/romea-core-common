// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__MONITORING__RATEMONITORING_HPP_
#define ROMEA_CORE_COMMON__MONITORING__RATEMONITORING_HPP_

// std
#include <queue>
#include <atomic>

// romea
#include "romea_core_common/time/Time.hpp"
#include "romea_core_common/concurrency/SharedVariable.hpp"

namespace romea
{

class RateMonitoring
{
public:
  RateMonitoring();

  explicit RateMonitoring(const double & expectedRate);

  RateMonitoring(const RateMonitoring & RateMonitoring);

  void initialize(const double & expectedRate);

  double update(const Duration & duration);

  double getRate()const;

  bool timeout(const Duration & duration);

private:
  size_t windowSize_;

  Duration lastPeriod_;
  SharedVariable<Duration> lastDuration_;
  std::queue<long long int> periods_;
  long long int periodsSum_;
  std::atomic<double> rate_;
};


}  // namespace romea

#endif  // ROMEA_CORE_COMMON__MONITORING__RATEMONITORING_HPP_
