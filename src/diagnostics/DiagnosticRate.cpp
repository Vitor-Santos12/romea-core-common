#include "romea_common/diagnostic/DiagnosticRate.hpp"
#include <sstream>

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticRate::DiagnosticRate(const std::string &name,
                               const double & minimalRate,
                               const double & espilon):
  rateMonitoring_(minimalRate),
  minimalRate_(minimalRate),
  epsilon_(espilon),
  report_()
{
  report_.info[name+"_rate"]="";
}

//-----------------------------------------------------------------------------
DiagnosticStatus DiagnosticRate::evaluate(const Duration & stamp)
{
  double rate=rateMonitoring_.update(stamp);
  report_.message = report_.info.begin()->first;

  if(rate > minimalRate_-epsilon_)
  {
    this->report_.status=DiagnosticStatus::OK;
    this->report_.message+= " is OK.";
  }
  else
  {
    this->report_.status=DiagnosticStatus::ERROR;
    this->report_.message+= " is too low.";
  }

  report_.info.begin()->second=toStringInfoValue(rateMonitoring_.getRate());
  return report_.status;
}

//-----------------------------------------------------------------------------
const DiagnosticReport & DiagnosticRate::getReport()const
{
  return report_;
}

}// namespace



