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


#ifndef ROMEA_CORE_COMMON__CONTROL__PID_HPP_
#define ROMEA_CORE_COMMON__CONTROL__PID_HPP_

#include "romea_core_common/time/Time.hpp"

namespace romea
{

class PID
{
public:
  struct Parameters
  {
    double kp;
    double ki;
    double kd;
    double imin;
    double imax;
  };

  PID(const Parameters & parameters);

  PID(
    const double & kp,
    const double & ki,
    const double & kd,
    const double & imin,
    const double & imax);

  double compute(
    const Duration & stamp,
    const double & setpoint,
    const double & measurement);

  const double & kp() const;
  const double & ki() const;
  const double & kd() const;

  void reset();

private:
  void computeDt_(const Duration & stamp);

  void computeDerivative_(const double & error);

  void updateIntegral_(const double & error);

private:
  double dt_;
  double kp_;
  double ki_;
  double kd_;
  double imax_;
  double imin_;
  double i_;
  double d_;

  double previous_error_;
  Duration previous_error_stamp_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTROL_PID_HPP_
