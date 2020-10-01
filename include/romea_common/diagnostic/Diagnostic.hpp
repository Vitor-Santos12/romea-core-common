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

  Diagnostic(const DiagnosticStatus & status,
             const std::string & message);

  DiagnosticStatus status;
  std::string message;
};

std::ostream & operator <<(std::ostream & os, const Diagnostic & diagnostic);

DiagnosticStatus worseStatus(const std::list<Diagnostic> & diagnostics);

bool allOK(const std::list<Diagnostic> & diagnostics);

}

#endif
