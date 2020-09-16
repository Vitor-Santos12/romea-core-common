#include "romea_common/diagnostic/DiagnosticStatus.hpp"

namespace romea {

//-----------------------------------------------------------------------------
DiagnosticStatus worse(DiagnosticStatus status1,DiagnosticStatus status2)
{
  return status1>=status2 ? status1 : status2;
}


}// namespace



