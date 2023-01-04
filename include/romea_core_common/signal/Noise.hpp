// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__SIGNAL__NOISE_HPP_
#define ROMEA_CORE_COMMON__SIGNAL__NOISE_HPP_

namespace romea
{

double convertNoiseDensityToNoiseStd(
  const double & noiseDensity,
  const double & frequency);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_SIGNAL_NOISE_HPP_
