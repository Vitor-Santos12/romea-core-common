#ifndef ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPEQUALTO_HPP_
#define ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPEQUALTO_HPP_

// std
#include <string>

// romea
#include "romea_core_common/diagnostic/Checkup.hpp"

namespace romea {


template <typename T>
class  CheckupEqualTo : public Checkup<T>
{
public:
  CheckupEqualTo(const std::string &name,
                 const T & desired_value,
                 const T & epsilon,
                 const Diagnostic & initialDiagnostic = Diagnostic());

  DiagnosticStatus evaluate(const T & value) override;
};

//-----------------------------------------------------------------------------
template <typename T>
CheckupEqualTo<T>::CheckupEqualTo(const std::string & name,
                                  const T & desired_value,
                                  const T & epsilon,
                                  const Diagnostic & initialDiagnostic):
  Checkup<T>(name, desired_value, epsilon, initialDiagnostic)
{
}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckupEqualTo<T>::evaluate(const T & value)
{
  if (value < this->value_to_compare_with_-this->epsilon_)
  {
    this->setDiagnostic_(DiagnosticStatus::ERROR, " is too low.");
  }else if (value > this->value_to_compare_with_ + this->epsilon_){
    this->setDiagnostic_(DiagnosticStatus::ERROR, " is too high.");
  }else{
    this->setDiagnostic_(DiagnosticStatus::OK, " is OK.");
  }

  this->setValue_(value);
  return this->getStatus_();
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPEQUALTO_HPP_
