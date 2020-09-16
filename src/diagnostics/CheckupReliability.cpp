#include "romea_common/diagnostic/CheckupReliability.hpp"
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
  report_.diagnostics.push_back(Diagnostic());
}

//-----------------------------------------------------------------------------
DiagnosticStatus DiagnosticReliability2::evaluate(const double & reliability)
{
  if(reliability < low_reliability_theshold_ )
  {
    setDiagnostic_(DiagnosticStatus::ERROR," is too low.");
  }
  else if(reliability < high_reliability_theshold_)
  {
    setDiagnostic_(DiagnosticStatus::WARN," is uncertain.");
  }
  else
  {
    setDiagnostic_(DiagnosticStatus::OK," is high.");
  }

  setRelabilityValue_(reliability);
  return report_.diagnostics.front().status;
}

//-----------------------------------------------------------------------------
const DiagnosticReport & DiagnosticReliability2::getReport()const
{
  return report_;
}

//-----------------------------------------------------------------------------
void DiagnosticReliability2::setRelabilityValue_(const double & reliability)
{
  report_.info.begin()->second=toStringInfoValue(reliability);
}

//-----------------------------------------------------------------------------
void DiagnosticReliability2::setDiagnostic_(const DiagnosticStatus & status,
                                         const std::string & messageEnd)
{
  Diagnostic & message = report_.diagnostics.front();
  message.message = report_.info.begin()->first + messageEnd;
  message.status = status;
}

}// namespace



