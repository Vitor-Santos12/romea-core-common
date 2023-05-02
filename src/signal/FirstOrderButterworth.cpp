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


// romea
#include "romea_core_common/signal/FirstOrderButterworth.hpp"

// std
#include <cassert>

namespace romea
{

//-----------------------------------------------------------------------------
FirstOrderButterworth::FirstOrderButterworth(const double & weighting)
: weighting_(weighting),
  complementaryWeighting_((1 - weighting) / 2),
  filteredValue_(0),
  previousMeasuredValue_(),
  isInitialized_(false)
{
  assert(weighting >= 0 && weighting <= 1);
}


//-----------------------------------------------------------------------------
double FirstOrderButterworth::update(const double & measuredValue)
{
  if (isInitialized_) {
    filteredValue_ = weighting_ * filteredValue_ +
      complementaryWeighting_ * measuredValue +
      complementaryWeighting_ * previousMeasuredValue_;
  } else {
    filteredValue_ = measuredValue;
    previousMeasuredValue_ = measuredValue;
    isInitialized_ = true;
  }

  previousMeasuredValue_ = measuredValue;

  return filteredValue_;
}

//-----------------------------------------------------------------------------
void FirstOrderButterworth::reset()
{
  filteredValue_ = 0;
  previousMeasuredValue_ = 0;
  isInitialized_ = false;
}

}  // namespace romea
