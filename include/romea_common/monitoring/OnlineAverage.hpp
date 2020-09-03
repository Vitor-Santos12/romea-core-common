#ifndef __OnlineAverage_H__
#define __OnlineAverage_H__

//std
#include <queue>
#include <atomic>
#include <cstdlib>
#include <mutex>

namespace romea {


class OnlineAverage
{

public :


  OnlineAverage(const double & averagePrecision,size_t windowSize);

  OnlineAverage(const double & averagePrecision);

  OnlineAverage(const OnlineAverage & onlineAverage);

  virtual ~OnlineAverage()=default;

public :

  virtual void setWindowSize(const size_t  & windowSize);

  const size_t & getWindowSize() const;

  bool isAvailable()const;


  virtual void update(const double &value);

  double getAverage()const;


protected :

  size_t index_;
  size_t windowSize_;

  int multiplier_;
  std::vector<long long int> data_;
  long long int sumOfData_;

  std::atomic<double> average_;

};

}

#endif
