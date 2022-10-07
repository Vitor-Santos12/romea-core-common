#include "romea_core_common/diagnostic/CheckupRate.hpp"
#include <sstream>
#include <iostream>

namespace romea {

//-----------------------------------------------------------------------------
CheckupRate::CheckupRate(const std::string &name,
                         const double & minimalRate,
                         const double & espilon):
  rateMonitoring_(minimalRate),
  minimalRate_(minimalRate),
  epsilon_(espilon),
  report_()
{
  report_.info[name+"_rate"]="";
  report_.diagnostics.push_back(Diagnostic(DiagnosticStatus::ERROR,"no data received from "+name));
}


//-----------------------------------------------------------------------------
DiagnosticStatus CheckupRate::evaluate(const Duration & stamp)
{
  double rate=rateMonitoring_.update(stamp);

  std::lock_guard<std::mutex> lock(mutex_);
  if(rate > minimalRate_-epsilon_)
  {
    setDiagnostic_(DiagnosticStatus::OK," is OK.");
  }
  else
  {
    setDiagnostic_(DiagnosticStatus::ERROR," is too low.");
  }

  setRateValue_();
  return report_.diagnostics.front().status;
}

//-----------------------------------------------------------------------------
DiagnosticReport CheckupRate::getReport() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return report_;
}

//-----------------------------------------------------------------------------
void CheckupRate::setDiagnostic_(const DiagnosticStatus & status,
                                 const std::string & diagnosticEnd)
{
  Diagnostic & message = report_.diagnostics.front();
  message.message = report_.info.begin()->first + diagnosticEnd;
  message.status = status;
}

//-----------------------------------------------------------------------------
void CheckupRate::setRateValue_()
{
  report_.info.begin()->second=toStringInfoValue(rateMonitoring_.getRate());
}

//-----------------------------------------------------------------------------
bool CheckupRate::heartBeatCallback(const Duration & stamp)
{
  if(rateMonitoring_.timeout(stamp))
  {
    std::lock_guard<std::mutex> lock(mutex_);
    setDiagnostic_(DiagnosticStatus::STALE," timeout");
    setRateValue_();
    return false;
  }
  return true;
}


}// namespace



