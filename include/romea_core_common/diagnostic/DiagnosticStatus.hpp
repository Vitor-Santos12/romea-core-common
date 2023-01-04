// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef _ROMEA_CORE_COMMON__DIAGNOSTIC__DIAGNOSTICSTATUS_HPP_
#define _ROMEA_CORE_COMMON__DIAGNOSTIC__DIAGNOSTICSTATUS_HPP_

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

std::ostream & operator<<(std::ostream & os, const DiagnosticStatus & status);

DiagnosticStatus worse(const DiagnosticStatus & status1, const DiagnosticStatus & status2);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__DIAGNOSTIC__DIAGNOSTICSTATUS_HPP_
