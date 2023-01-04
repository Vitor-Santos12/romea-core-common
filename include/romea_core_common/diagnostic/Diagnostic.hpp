// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__DIAGNOSTIC__DIAGNOSTIC_HPP_
#define ROMEA_CORE_COMMON__DIAGNOSTIC__DIAGNOSTIC_HPP_

// std
#include <list>
#include <string>

// romea
#include "romea_core_common/diagnostic/DiagnosticStatus.hpp"

namespace romea
{

struct Diagnostic
{
  Diagnostic();

  Diagnostic(
    const DiagnosticStatus & status,
    const std::string & message);

  DiagnosticStatus status;
  std::string message;
};

std::ostream & operator<<(std::ostream & os, const Diagnostic & diagnostic);

DiagnosticStatus worseStatus(const std::list<Diagnostic> & diagnostics);

bool allOK(const std::list<Diagnostic> & diagnostics);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__DIAGNOSTIC__DIAGNOSTIC_HPP_
