#ifndef _romea_CheckEqualTo_hpp_
#define _romea_CheckEqualTo_hpp_

#include "Checkup.hpp"

namespace romea {


template <typename T>
class  CheckupEqualTo : public Checkup<T>
{

public:

  CheckupEqualTo(const std::string &name,
                 const T & desired_value,
                 const T & epsilon,
                 const Diagnostic & initialDiagnostic=Diagnostic());

  DiagnosticStatus evaluate(const T & value) override;

};

//-----------------------------------------------------------------------------
template <typename T>
CheckupEqualTo<T>::CheckupEqualTo(const std::string & name,
                                  const T & desired_value,
                                  const T & epsilon,
                                  const Diagnostic & initialDiagnostic):
  Checkup<T>(name,desired_value,epsilon,initialDiagnostic)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckupEqualTo<T>::evaluate(const T & value)
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
