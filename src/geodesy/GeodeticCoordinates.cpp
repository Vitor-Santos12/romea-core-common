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
