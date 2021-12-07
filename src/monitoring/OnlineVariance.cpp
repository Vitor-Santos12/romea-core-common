#include "romea_core_common/monitoring/OnlineVariance.hpp"

//std
#include <cassert>

namespace romea {


//-----------------------------------------------------------------------------
OnlineVariance::OnlineVariance(const double & averagePrecision,size_t windowSize):
  OnlineAverage(averagePrecision,windowSize),
  windowSizeMinusOne_(windowSize-1),
  squaredMultiplier_(multiplier_*multiplier_),
  squaredData_(),
  sumOfSquaredData_(),
  variance_(0)
{

}

//-----------------------------------------------------------------------------
OnlineVariance::OnlineVariance(const double & averagePrecision):
  OnlineVariance(averagePrecision,0)

{

}

//-----------------------------------------------------------------------------
OnlineVariance::OnlineVariance(const OnlineVariance & onlineVariance):
  OnlineAverage(onlineVariance),
  windowSizeMinusOne_(onlineVariance.windowSizeMinusOne_),
  squaredMultiplier_(onlineVariance.squaredMultiplier_),
  squaredData_(onlineVariance.squaredData_),
  sumOfSquaredData_(onlineVariance.sumOfSquaredData_),
  variance_(onlineVariance.variance_.load())
{
}

//-----------------------------------------------------------------------------
void OnlineVariance::setWindowSize(const size_t & windowSize)
{
  windowSize_=windowSize;
  windowSizeMinusOne_ = windowSize-1;
  data_.reserve(windowSize_);
  squaredData_.reserve(windowSize_);

}

//-----------------------------------------------------------------------------
double OnlineVariance::getVariance()const
{
  return variance_.load();
}


//-----------------------------------------------------------------------------
void OnlineVariance::update(const double & value)
{

  long long int integerValue = static_cast<long long int>(value*multiplier_);
  long long int squaredIntegerValue = integerValue*integerValue;

  sumOfData_+=integerValue;
  sumOfSquaredData_ += squaredIntegerValue;

  if(data_.size()!=windowSize_)
  {
    data_.push_back(integerValue);
    squaredData_.push_back(squaredIntegerValue);
  }
  else
  {
    sumOfData_-=data_[index_];
    sumOfSquaredData_ -= squaredData_[index_];

    data_[index_]= integerValue;
    squaredData_[index_] = squaredIntegerValue;
  }

  double average = sumOfData_/(double(multiplier_)*data_.size());
  double squaredAverage= (sumOfSquaredData_)/double(squaredMultiplier_);
  double variance = (squaredAverage - data_.size()*average*average)/(windowSizeMinusOne_);
  average_.store(average);
  variance_.store(variance);


  index_ = (index_+1)%windowSize_;
}

}
