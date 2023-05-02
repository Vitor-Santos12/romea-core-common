// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


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
