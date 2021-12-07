#ifndef _romea_DiagnosticStatus_hpp_
#define _romea_DiagnosticStatus_hpp_

#include <ostream>
#include <string>

namespace romea
{

enum class DiagnosticStatus
{
  OK = 0,
  WARN = 1,
  ERROR = 2,
  STALE = 3
};

std::string toString(const DiagnosticStatus & status);

std::ostream& operator<<(std::ostream & os, const DiagnosticStatus & status);

DiagnosticStatus worse(const DiagnosticStatus & status1 , const DiagnosticStatus &status2);

}

#endif
