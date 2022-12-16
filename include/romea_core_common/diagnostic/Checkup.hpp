#ifndef ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUP_HPP_
#define ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUP_HPP_

// std
#include <limits>
#include <sstream>
#include <string>
#include <mutex>

// romea
#include "romea_core_common/diagnostic/DiagnosticReport.hpp"

namespace romea {


template <typename T>
class  Checkup
{
public:
  Checkup(const std::string &name,
          const T & value_to_compare_with_,
          const T & epsilon,
          const Diagnostic & diagnostic = Diagnostic());

  virtual ~Checkup() = default;

  virtual DiagnosticStatus evaluate(const T & value) = 0;

  const DiagnosticReport & getReport() const;

  void timeout();

protected:
  void setValue_(const T & value);

  void setDiagnostic_(const DiagnosticStatus & status,
                      const std::string & messageEnd);

  const DiagnosticStatus & getStatus_() const;

protected:
  T value_to_compare_with_;
  T epsilon_;

  mutable std::mutex mutex_;
  DiagnosticReport report_;
};

//-----------------------------------------------------------------------------
template <typename T>
Checkup<T>::Checkup(const std::string & name,
                    const T & value_to_compare_with,
                    const T & epsilon,
                    const Diagnostic & diagnostic):
  value_to_compare_with_(value_to_compare_with),
  epsilon_(epsilon),
  mutex_(),
  report_()
{
  report_.diagnostics.push_back(diagnostic);
  report_.info[name] = "";
}

//-----------------------------------------------------------------------------
template <typename T>
const DiagnosticReport & Checkup<T>::getReport() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return report_;
}

//-----------------------------------------------------------------------------
template <typename T>
void Checkup<T>::timeout()
{
  std::lock_guard<std::mutex> lock(mutex_);
  setDiagnostic_(DiagnosticStatus::STALE, " timeout.");
  report_.info.begin()->second = "";
}


//-----------------------------------------------------------------------------
template <typename T>
void Checkup<T>::setValue_(const T & value)
{
  report_.info.begin()->second = toStringInfoValue(value);
}

//-----------------------------------------------------------------------------
template <typename T>
void Checkup<T>::setDiagnostic_(const DiagnosticStatus & status,
                                const std::string & messageEnd)
{
  Diagnostic & diagnostic = report_.diagnostics.front();
  diagnostic.message = report_.info.begin()->first + messageEnd;
  diagnostic.status = status;
}

//-----------------------------------------------------------------------------
template <typename T>
const DiagnosticStatus & Checkup<T>::getStatus_() const
{
  return this->report_.diagnostics.front().status;
}


}  // namespace romea

#endif  // ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUP_HPP_
