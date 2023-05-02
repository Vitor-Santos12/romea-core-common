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


#include "romea_core_common/diagnostic/DiagnosticReport.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
DiagnosticReport::DiagnosticReport()
: diagnostics(),
  info()
{
}


//-----------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const DiagnosticReport & report)
{
  os << " Messages : " << std::endl;
  for (const auto & message : report.diagnostics) {
    os << " " << message << std::endl;
  }
  os << " Additional info :" << std::endl;
  for (const auto & [info_name, info_status] : report.info) {
    os << " " << info_name << " = " << info_status << std::endl;
  }
  return os;
}

//-----------------------------------------------------------------------------
DiagnosticReport & operator+=(DiagnosticReport & report1, const DiagnosticReport & report2)
{
  report1.diagnostics.insert(
    std::end(report1.diagnostics),
    std::cbegin(report2.diagnostics),
    std::cend(report2.diagnostics));

  report1.info.insert(
    std::cbegin(report2.info),
    std::cend(report2.info));

  return report1;
}


}  // namespace  romea
