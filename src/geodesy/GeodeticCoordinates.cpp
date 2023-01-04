// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include "romea_core_common/geodesy/GeodeticCoordinates.hpp"

// std
#include <cmath>
#include <cassert>

namespace romea
{

//--------------------------------------------------------------------------
GeodeticCoordinates makeGeodeticCoordinates(
  const double & latitude,
  const double & longitude,
  const double & altitude)
{
  assert(latitude >= -M_PI_2 && latitude <= M_PI_2);
  assert(longitude >= -M_PI && longitude <= M_PI);

  GeodeticCoordinates geodetic_coordinates;
  geodetic_coordinates.latitude = latitude;
  geodetic_coordinates.longitude = longitude;
  geodetic_coordinates.altitude = altitude;
  return geodetic_coordinates;
}

//--------------------------------------------------------------------------
GeodeticCoordinates makeGeodeticCoordinates(
  const WGS84Coordinates & wgs84Coordinates,
  const double & altitude)
{
  GeodeticCoordinates geodetic_coordinates;
  geodetic_coordinates.latitude = wgs84Coordinates.latitude;
  geodetic_coordinates.longitude = wgs84Coordinates.longitude;
  geodetic_coordinates.altitude = altitude;
  return geodetic_coordinates;
}


//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const GeodeticCoordinates & geodeticCoordinates)
{
  os << static_cast<WGS84Coordinates>(geodeticCoordinates);
  os << "altitude in meter" << geodeticCoordinates.altitude;
  return os;
}

}  // namespace romea
