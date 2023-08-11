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
#include <thread>
#include <functional>

// romea
#include "romea_core_common/time/Timer.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
Timer::Timer(
  std::function<void(void)> callbackFunction,
  const Duration & period)
: callbackFunction_(callbackFunction),
  period_(period),
  thread_(),
  running_(false)
{
}

//-----------------------------------------------------------------------------
void Timer::start()
{
  running_ = true;
  thread_ = std::thread(
    [&]()
    {
      while (running_) {
        auto delta = std::chrono::steady_clock::now() + period_;
        callbackFunction_();
        std::this_thread::sleep_until(delta);
      }
    });
}

//-----------------------------------------------------------------------------
void Timer::stop()
{
  running_ = false;
  thread_.join();
}

//-----------------------------------------------------------------------------
Timer::~Timer()
{
  if (running_) {
    stop();
  }
}

}  // namespace romea
