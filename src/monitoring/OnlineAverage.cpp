//romea
#include "romea_common/monitoring/OnlineAverage.hpp"

namespace romea {

//-----------------------------------------------------------------------------
OnlineAverage::OnlineAverage(const double & averagePrecision,size_t windowSize):
  index_(0),
  windowSize_(windowSize),
  multiplier_(static_cast<int>(1/averagePrecision)),
  data_(),
  sumOfData_(),
  average_()
{
}

//-----------------------------------------------------------------------------
OnlineAverage::OnlineAverage(const double & averagePrecision):
  OnlineAverage::OnlineAverage(averagePrecision,0)
{

}

//-----------------------------------------------------------------------------
OnlineAverage::OnlineAverage(const OnlineAverage & onlineAverage):
  index_(onlineAverage.index_),
  windowSize_(onlineAverage.windowSize_),
  multiplier_(onlineAverage.multiplier_),
  data_(onlineAverage.data_),
  sumOfData_(onlineAverage.sumOfData_),
  average_(onlineAverage.average_.load())
{
}

//-----------------------------------------------------------------------------
void OnlineAverage::setWindowSize(const size_t & windowSize)
{
  windowSize_=windowSize;
  data_.reserve(windowSize_);
}


//-----------------------------------------------------------------------------
const size_t & OnlineAverage::getWindowSize() const
{
  return windowSize_;
}


//-----------------------------------------------------------------------------
double OnlineAverage::getAverage()const
{
  return average_.load();
}


//-----------------------------------------------------------------------------
void OnlineAverage::update(const double & value)
{

  long long int integerValue = static_cast<long long int>(value*multiplier_);


  sumOfData_+=integerValue;
  if(data_.size()!=windowSize_)
  {
    data_.push_back(integerValue);
  }
  else
  {
    sumOfData_-=data_[index_];
    data_[index_]= integerValue;
  }
  average_.store(sumOfData_/(double(multiplier_)*data_.size()));
  index_ = (index_+1)%windowSize_;
}


//-----------------------------------------------------------------------------
bool OnlineAverage::isAvailable()const
{
  return data_.size() == windowSize_;
}


}
