#ifndef _romea_DiagnosticStatus_hpp_
#define _romea_DiagnosticStatus_hpp_


namespace romea
{

enum class DiagnosticStatus
{
  OK = 0,
  WARN = 1,
  ERROR = 2,
  STALE = 3
};

DiagnosticStatus worse(DiagnosticStatus status1,DiagnosticStatus status2);

}

#endif
