// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__DIAGNOSTIC__CHECKUPLOWERTHAN_HPP_
#define ROMEA_CORE_COMMON__DIAGNOSTIC__CHECKUPLOWERTHAN_HPP_

// std
#include <string>

// romea
#include "romea_core_common/diagnostic/Checkup.hpp"

namespace romea
{


template<typename T>
class CheckupLowerThan : public Checkup<T>
{
public:
  CheckupLowerThan(
    const std::string & name,
    const T & maximal_value,
    const T & epsilon,
    const Diagnostic & diagnostic = Diagnostic());

  DiagnosticStatus evaluate(const T & value) override;
};


//-----------------------------------------------------------------------------
template<typename T>
CheckupLowerThan<T>::CheckupLowerThan(
  const std::string & name,
  const T & maximal_value,
  const T & epsilon,
  const Diagnostic & diagnostic)
: Checkup<T>(name, maximal_value, epsilon, diagnostic)
{
}

//-----------------------------------------------------------------------------
template<typename T>
DiagnosticStatus CheckupLowerThan<T>::evaluate(const T & value)
{
  std::lock_guard<std::mutex> lock(this->mutex_);
  if (value < this->value_to_compare_with_ + this->epsilon_) {
    this->setDiagnostic_(DiagnosticStatus::OK, " is OK.");
  } else {
    this->setDiagnostic_(DiagnosticStatus::ERROR, " is too high.");
  }

  this->setValue_(value);
  return this->getStatus_();
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__DIAGNOSTIC__CHECKUPLOWERTHAN_HPP_
