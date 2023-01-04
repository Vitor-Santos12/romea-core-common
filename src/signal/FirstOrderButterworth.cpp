// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

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
