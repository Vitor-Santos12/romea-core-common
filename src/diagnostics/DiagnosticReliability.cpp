#include "romea_common/diagnostic/DiagnosticReliability.hpp"
#include <sstream>

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticReliability2::DiagnosticReliability2(const std::string &name,
                                             const double & low_reliability_theshold,
                                             const double & high_reliability_theshold):
  low_reliability_theshold_(low_reliability_theshold),
  high_reliability_theshold_(high_reliability_theshold),
  report_()
{
  report_.info[name]="";
}

//-----------------------------------------------------------------------------
DiagnosticStatus DiagnosticReliability2::evaluate(const double & reliability)
{
  report_.message = report_.info.begin()->first;

  if(reliability < low_reliability_theshold_ )
  {
    report_.status=DiagnosticStatus::ERROR;
    report_.message += " is too low.";
  }
  else if(reliability < high_reliability_theshold_)
  {
    report_.status=DiagnosticStatus::WARN;
    report_.message += " is uncertain.";
  }
  else
  {
    report_.status=DiagnosticStatus::OK;
    report_.message += " is high.";
  }

  report_.info.begin()->second=toStringInfoValue(reliability);
  return report_.status;
}

//-----------------------------------------------------------------------------
const DiagnosticReport & DiagnosticReliability2::getReport()const
{
  return report_;
}

}// namespace



