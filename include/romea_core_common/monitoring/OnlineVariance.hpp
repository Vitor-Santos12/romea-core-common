// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON_MONITORING_ONLINEVARIANCE_HPP_
#define ROMEA_CORE_COMMON_MONITORING_ONLINEVARIANCE_HPP_

// std
#include <vector>

// local
#include "romea_core_common/monitoring/OnlineAverage.hpp"

namespace romea
{

class OnlineVariance : public OnlineAverage
{
public:
  explicit OnlineVariance(const double & averagePrecision);

  OnlineVariance(const double & averagePrecision, size_t windowSize);

  OnlineVariance(const OnlineVariance & onlineVariance);

  virtual ~OnlineVariance() = default;

public:
  void setWindowSize(const size_t & windowSize) override;

  void update(const double & value) override;

  void reset() override;

  double getVariance()const;

private:
  size_t windowSizeMinusOne_;
  int squaredMultiplier_;

  std::vector<long long int> squaredData_;
  long long int sumOfSquaredData_;
  double variance_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_MONITORING_ONLINEVARIANCE_HPP_
