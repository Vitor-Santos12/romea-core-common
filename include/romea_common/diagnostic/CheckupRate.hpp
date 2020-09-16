#ifndef _romea_DiagnosticRate_hpp_
#define _romea_DiagnosticRate_hpp_

#include "DiagnosticReport.hpp"
#include "../monitoring/RateMonitoring.hpp"

namespace romea {


class  CheckupRate
{
public:


  CheckupRate(const std::string &name,
              const double & minimalRate,
              const double & espilon= std::numeric_limits<double>::epsilon());

  DiagnosticStatus evaluate(const Duration & stamp);

  const DiagnosticReport & getReport()const;

private :

  void setRateValue_();

  void setDiagnostic_(const DiagnosticStatus & status,
                      const std::string & diagnosticEnd);

private :

  RateMonitoring rateMonitoring_;

  double minimalRate_;
  double epsilon_;

  DiagnosticReport report_;
};

}

#endif



