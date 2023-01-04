// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON_GEODESY_WGS84COORDINATES_HPP_
#define ROMEA_CORE_COMMON_GEODESY_WGS84COORDINATES_HPP_

#include <ostream>

namespace romea {

struct WGS84Coordinates
{
  double latitude;
  double longitude;
};

WGS84Coordinates makeWGS84Coordinates(const double & latitude,
                                      const double & longitude);

std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_GEODESY_WGS84COORDINATES_HPP_
