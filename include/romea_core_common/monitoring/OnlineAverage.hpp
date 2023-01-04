// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON_MONITORING_ONLINEAVERAGE_HPP_
#define ROMEA_CORE_COMMON_MONITORING_ONLINEAVERAGE_HPP_

// std
#include <queue>
#include <atomic>
#include <cstdlib>
#include <mutex>
#include <vector>

namespace romea
{


class OnlineAverage
{
public:
  explicit OnlineAverage(const double & averagePrecision);

  OnlineAverage(const double & averagePrecision, size_t windowSize);

  OnlineAverage(const OnlineAverage & onlineAverage);

  virtual ~OnlineAverage() = default;

public:
  virtual void setWindowSize(const size_t & windowSize);

  const size_t & getWindowSize() const;

  bool isAvailable()const;


  virtual void update(const double & value);

  double getAverage()const;

  virtual void reset();

protected:
  size_t index_;
  size_t windowSize_;
  int multiplier_;

  mutable std::mutex mutex_;
  std::vector<long long int> data_;
  long long int sumOfData_;
  double average_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_MONITORING_ONLINEAVERAGE_HPP_
