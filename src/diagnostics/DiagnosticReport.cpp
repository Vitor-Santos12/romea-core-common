// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#include "romea_core_common/diagnostic/DiagnosticReport.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
DiagnosticReport::DiagnosticReport()
: diagnostics(),
  info()
{
}


//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const DiagnosticReport & report)
{
  os << " Messages : " << std::endl;
  for (const auto message : report.diagnostics) {
    os << " " << message << std::endl;
  }
  os << " Additional info :" << std::endl;
  for (const auto & [info_name, info_status] : report.info) {
    os << " " << info_name << " = " << info_status << std::endl;
  }
  return os;
}

//-----------------------------------------------------------------------------
DiagnosticReport & operator+=(DiagnosticReport & report1, const DiagnosticReport & report2)
{
  report1.diagnostics.insert(
    std::end(report1.diagnostics),
    std::cbegin(report2.diagnostics),
    std::cend(report2.diagnostics));

  report1.info.insert(
    std::cbegin(report2.info),
    std::cend(report2.info));

  return report1;
}


}  // namespace  romea
