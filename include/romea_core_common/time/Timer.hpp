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


#ifndef ROMEA_CORE_COMMON__TIME__TIMER_HPP_
#define ROMEA_CORE_COMMON__TIME__TIMER_HPP_

// std
#include <thread>
#include <functional>

// romea
#include "romea_core_common/time/Time.hpp"

namespace romea
{
namespace core
{

class Timer
{
public:
  Timer(
    std::function<void(void)> callbackFunction,
    const Duration & period);

  void start();

  void stop();

  ~Timer();

private:
  std::function<void(void)> callbackFunction_;
  Duration period_;

  std::thread thread_;
  bool running_;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__TIME__TIMER_HPP_
