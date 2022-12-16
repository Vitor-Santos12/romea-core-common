#include "romea_core_common/diagnostic/DiagnosticStatus.hpp"

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticStatus worse(const DiagnosticStatus & status1,
                       const DiagnosticStatus & status2)
{
  return status1 >= status2 ? status1 : status2;
}

//-----------------------------------------------------------------------------
std::string toString(const DiagnosticStatus & status)
{
  switch (status) {
  case DiagnosticStatus::OK:
    return "OK";
    break;
  case DiagnosticStatus::WARN:
    return "WARN";
    break;
  case DiagnosticStatus::ERROR:
    return "ERROR";
    break;
  case DiagnosticStatus::STALE:
    return "STALE";
    break;
  default:
    return "";
    break;
  }
}

//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream & os, const DiagnosticStatus & status)
{
  os << toString(status);
  return os;
}



}  // namespace romea



