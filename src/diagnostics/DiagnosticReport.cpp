#include "romea_common/diagnostic/DiagnosticReport.hpp"

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticReport::DiagnosticReport():
  status(DiagnosticStatus::STALE),
  message(),
  info()
{
}

}// namespace



