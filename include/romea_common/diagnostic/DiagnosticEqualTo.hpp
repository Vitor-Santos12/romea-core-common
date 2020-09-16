#ifndef _romea_DiagnosticEqualTo2_hpp_
#define _romea_DiagnosticEqualTo2_hpp_

#include "DiagnosticCompareTo.hpp"

namespace romea {


template <typename T>
class  DiagnosticEqualTo2 final : public DiagnosticCompareTo<T>
{

public:

  DiagnosticEqualTo2(const std::string &name,
                     const T & desired_value,
                     const T & epsilon = std::numeric_limits<T>::epsilon());

  DiagnosticStatus evaluate(const T & value) override;

};

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticEqualTo2<T>::DiagnosticEqualTo2(const std::string & name,
                                          const T & desired_value,
                                          const T & epsilon):
  DiagnosticCompareTo<T>(name,desired_value,epsilon)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus DiagnosticEqualTo2<T>::evaluate(const T & value)
{
  if(value < this->value_to_compare_with_-this->epsilon_)
  {
    this->report_.status=DiagnosticStatus::ERROR;
    this->report_.message=this->getValueName_()+" is too low.";
  }
  else if(value > this->value_to_compare_with_+this->epsilon_)
  {
    this->report_.status=DiagnosticStatus::ERROR;
    this->report_.message=this->getValueName_()+" is too high.";
  }
  else
  {
    this->report_.status=DiagnosticStatus::OK;
    this->report_.message=this->getValueName_()+" is OK.";
  }

  this->setValue_(value);
  return this->report_.status;
}


}

#endif
