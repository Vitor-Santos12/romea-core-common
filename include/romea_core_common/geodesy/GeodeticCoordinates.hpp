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
