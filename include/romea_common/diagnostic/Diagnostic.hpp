#ifndef _romea_Diagnostic_hpp_
#define _romea_Diagnostic_hpp_

//std
#include <list>

//romea
#include "DiagnosticStatus.hpp"

namespace romea
{

struct Diagnostic
{
  Diagnostic();

  DiagnosticStatus status;
  std::string message;
};

std::ostream & operator <<(std::ostream & os, const Diagnostic & diagnostic);

DiagnosticStatus worseStatus(const std::list<Diagnostic> & diagnostics);

}

#endif
