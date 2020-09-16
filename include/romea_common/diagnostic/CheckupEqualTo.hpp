#ifndef _romea_DiagnosticEqualTo2_hpp_
#define _romea_DiagnosticEqualTo2_hpp_

#include "CheckupCompareWith.hpp"

namespace romea {


template <typename T>
class  CheckEqualTo final : public CheckCompareWith<T>
{

public:

  CheckEqualTo(const std::string &name,
               const T & desired_value,
               const T & epsilon = std::numeric_limits<T>::epsilon());

  DiagnosticStatus evaluate(const T & value) override;

};

//-----------------------------------------------------------------------------
template <typename T>
CheckEqualTo<T>::CheckEqualTo(const std::string & name,
                              const T & desired_value,
                              const T & epsilon):
  CheckCompareWith<T>(name,desired_value,epsilon)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckEqualTo<T>::evaluate(const T & value)
{
  if(value < this->value_to_compare_with_-this->epsilon_)
  {
    this->setDiagnostic_(DiagnosticStatus::ERROR," is too low.");
  }
  else if(value > this->value_to_compare_with_+this->epsilon_)
  {
    this->setDiagnostic_(DiagnosticStatus::ERROR," is too high.");
  }
  else
  {
    this->setDiagnostic_(DiagnosticStatus::OK," is OK.");
  }

  this->setValue_(value);
  return this->getStatus_();
}


}

#endif
