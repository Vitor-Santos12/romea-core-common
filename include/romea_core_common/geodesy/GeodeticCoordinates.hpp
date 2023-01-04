// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEODESY__GEODETICCOORDINATES_HPP_
#define ROMEA_CORE_COMMON__GEODESY__GEODETICCOORDINATES_HPP_

#include "romea_core_common/geodesy/WGS84Coordinates.hpp"

namespace romea
{

struct GeodeticCoordinates : WGS84Coordinates
{
  double altitude;
};

GeodeticCoordinates makeGeodeticCoordinates(
  const WGS84Coordinates & wgs84Coordinates,
  const double & altitude);

GeodeticCoordinates makeGeodeticCoordinates(
  const double & latitude,
  const double & longitude,
  const double & altitude);

std::ostream & operator<<(std::ostream & os, const GeodeticCoordinates & geodeticCoordinates);

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEODESY__GEODETICCOORDINATES_HPP_
