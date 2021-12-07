#include "romea_core_common/diagnostic/Diagnostic.hpp"

#include <cassert>

namespace romea {

//-----------------------------------------------------------------------------
Diagnostic::Diagnostic():
  status(DiagnosticStatus::STALE),
  message()
{
}

//-----------------------------------------------------------------------------
Diagnostic::Diagnostic(const DiagnosticStatus & status,
                       const std::string & message):
  status(status),
  message(message)

{

}

//-----------------------------------------------------------------------------
DiagnosticStatus worseStatus(const std::list<Diagnostic> & diagnostics)
{
  assert(!diagnostics.empty());

  auto it = std::cbegin(diagnostics);
  DiagnosticStatus status= it->status;

  while(++it!=std::cend(diagnostics))
  {
    status=worse(status,it->status);
  }

  return status;
}

//-----------------------------------------------------------------------------
bool allOK(const std::list<Diagnostic> & diagnostics)
{
  return worseStatus(diagnostics)==DiagnosticStatus::OK;
}

//-----------------------------------------------------------------------------
std::ostream & operator <<(std::ostream & os, const Diagnostic & diagnostic)
{
  os<< diagnostic.status <<" : "<< diagnostic.message;
  return os;
}


}// namespace



