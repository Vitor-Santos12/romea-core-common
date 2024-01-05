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


// std
#include <string>

// local
#include "romea_core_common/diagnostic/DiagnosticStatus.hpp"

namespace romea
{
namespace core
{

//-----------------------------------------------------------------------------
DiagnosticStatus worse(
  const DiagnosticStatus & status1,
  const DiagnosticStatus & status2)
{
  return status1 >= status2 ? status1 : status2;
}

//-----------------------------------------------------------------------------
std::string toString(const DiagnosticStatus & status)
{
  switch (status) {
    case DiagnosticStatus::OK:
      return "OK";
      break;
    case DiagnosticStatus::WARN:
      return "WARN";
      break;
    case DiagnosticStatus::ERROR:
      return "ERROR";
      break;
    case DiagnosticStatus::STALE:
      return "STALE";
      break;
    default:
      return "";
      break;
  }
}

//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const DiagnosticStatus & status)
{
  os << toString(status);
  return os;
}

}  // namespace core
}  // namespace romea
