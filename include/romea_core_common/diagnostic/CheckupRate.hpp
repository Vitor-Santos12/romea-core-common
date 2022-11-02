#ifndef _romea_DiagnosticRate_hpp_
#define _romea_DiagnosticRate_hpp_

#include "CheckupEqualTo.hpp"
#include "CheckupGreaterThan.hpp"
#include "../monitoring/RateMonitoring.hpp"

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

}

#endif



