#ifndef ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPGREATERTHAN_HPP_
#define ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPGREATERTHAN_HPP_

// std
#include <string>

// romea
#include "romea_core_common/diagnostic/Checkup.hpp"

namespace romea {



template <typename T>
class  CheckupGreaterThan : public Checkup<T>
{
public:
  CheckupGreaterThan(const std::string &name,
                     const T &minimal_value,
                     const T &epsilon,
                     const Diagnostic & diagnostic = Diagnostic());

  DiagnosticStatus evaluate(const T & value) override;
};

//-----------------------------------------------------------------------------
template< typename T>
CheckupGreaterThan<T>::CheckupGreaterThan(const std::string &name,
                                          const T &minimal_value,
                                          const T &epsilon,
                                          const Diagnostic & diagnostic):
  Checkup<T>(name, minimal_value, epsilon, diagnostic)
{
}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckupGreaterThan<T>::evaluate(const T & value)
{
  std::lock_guard<std::mutex> lock(this->mutex_);
  if (value > this->value_to_compare_with_ - this->epsilon_)
  {
    this->setDiagnostic_(DiagnosticStatus::OK, " is OK.");
  }else{
    this->setDiagnostic_(DiagnosticStatus::ERROR, " is too low.");
  }
  this->setValue_(value);
  return this->getStatus_();;
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPGREATERTHAN_HPP_



