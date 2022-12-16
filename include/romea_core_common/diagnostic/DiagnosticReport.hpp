#ifndef ROMEA_CORE_COMMON_DIAGNOSTIC_DIAGNOSTICREPORT_HPP_
#define ROMEA_CORE_COMMON_DIAGNOSTIC_DIAGNOSTICREPORT_HPP_

// std
#include <optional>
#include <sstream>
#include <string>
#include <list>
#include <map>

// romea
#include "romea_core_common/diagnostic/Diagnostic.hpp"

namespace romea
{

struct DiagnosticReport
{
  DiagnosticReport();
  std::list<Diagnostic> diagnostics;
  std::map<std::string, std::string> info;
};

std::ostream & operator <<(std::ostream & os, const DiagnosticReport & report);

DiagnosticReport & operator+=(DiagnosticReport & report1, const DiagnosticReport & report2);

//-----------------------------------------------------------------------------
template <typename T>
std::string toStringInfoValue(const T & infoValue)
{
  std::ostringstream os;
  os << infoValue;
  return os.str();
}

//-----------------------------------------------------------------------------
template <typename T>
void setReportInfo(DiagnosticReport & report,
                   const std::string & infoName,
                   const T & infoValue)
{
  report.info[infoName] = toStringInfoValue(infoValue);
}

//-----------------------------------------------------------------------------
template <typename T>
void setReportInfo(DiagnosticReport & report,
                   const std::string & infoName,
                   const std::optional<T> & infoValue)
{
  if (infoValue.has_value())
  {
    setReportInfo(report, infoName, *infoValue);
  } else {
    report.info[infoName] = "";
  }
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_DIAGNOSTIC_DIAGNOSTICREPORT_HPP_
