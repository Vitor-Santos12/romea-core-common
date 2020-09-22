#include "romea_common/diagnostic/DiagnosticReport.hpp"

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticReport::DiagnosticReport():
  diagnostics(),
  info()
{
}


//-----------------------------------------------------------------------------
std::ostream & operator <<(std::ostream & os, const DiagnosticReport & report)
{
  os<<" Messages : " <<std::endl;
  for(const auto message : report.diagnostics)
  {
    os << " "<< message << std::endl;
  }
  os<<" Additional info :"<< std::endl;
  //TODO use strutured binding >= c++17
  for(const auto p : report.info)
  {
    os<< " "<< p.first <<" = "<< p.second << std::endl;
  }
  return os;
}

//-----------------------------------------------------------------------------
DiagnosticReport & operator+=(DiagnosticReport & report1, const DiagnosticReport & report2)
{
  report1.diagnostics.insert(std::end(report1.diagnostics),
                          std::cbegin(report2.diagnostics),
                          std::cend(report2.diagnostics));

  report1.info.insert(std::cbegin(report2.info),
                      std::cend(report2.info));

  return report1;
}


}// namespace



