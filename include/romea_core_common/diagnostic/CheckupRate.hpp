#ifndef ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPRATE_HPP_
#define ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPRATE_HPP_

// std
#include <string>
#include <mutex>

// romea
#include "romea_core_common/diagnostic/CheckupEqualTo.hpp"
#include "romea_core_common/diagnostic/CheckupGreaterThan.hpp"
#include "romea_core_common/monitoring/RateMonitoring.hpp"

namespace romea {

template <typename CheckupType>
class  CheckupRate
{
public:
  CheckupRate(const std::string &name,
              const double & rate,
              const double & espilon);

  DiagnosticStatus evaluate(const Duration & stamp);

  bool heartBeatCallback(const Duration & stamp);

  DiagnosticReport getReport()const;

private :
  RateMonitoring rateMonitoring_;
  CheckupType checkup_;

  mutable std::mutex mutex_;
  DiagnosticReport report_;
};


using CheckupEqualToRate = CheckupRate<CheckupEqualTo<double>>;
using CheckupGreaterThanRate = CheckupRate<CheckupGreaterThan<double>>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_DIAGNOSTIC_CHECKUPRATE_HPP_ 



