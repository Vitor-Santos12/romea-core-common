#include "romea_common/diagnostic/DiagnosticReport.hpp"

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticReport::DiagnosticReport():
  status(DiagnosticStatus::STALE),
  message(),
  info()
{
}


////-----------------------------------------------------------------------------
//std::ostream & operator <<(std::ostream & os, const DiagnosticReport & report)
//{
//  os<<
//}

////-----------------------------------------------------------------------------
//DiagnosticReport & operator+=(DiagnosticReport & report1, const DiagnosticReport & report2)
//{

//}

////-----------------------------------------------------------------------------
//DiagnosticReport DiagnosticReport::operator+=(const DiagnosticReport & report)
//{
//  if(status==DiagnosticStatus::STALE)
//}


}// namespace



