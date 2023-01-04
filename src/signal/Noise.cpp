// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// local
#include "romea_core_common/signal/Noise.hpp"

// std
#include <cmath>

namespace romea
{

double convertNoiseDensityToNoiseStd(
  const double & noiseDensity,
  const double & frequency)
{
  return 1.57 * noiseDensity * std::sqrt(frequency);
}

}
