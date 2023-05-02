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
#include "romea_core_common/geodesy/WGS84Coordinates.hpp"

// std
#include <cassert>
#include <cmath>
#include <iomanip>

namespace romea
{

//--------------------------------------------------------------------------
WGS84Coordinates makeWGS84Coordinates(
  const double & latitude,
  const double & longitude)
{
  assert(latitude >= -M_PI_2 && latitude <= M_PI_2);
  assert(longitude >= -M_PI && longitude <= M_PI);
  return {latitude, longitude};
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates)
{
  os << std::setprecision(10);
  os << "latitude in radian :" << wgs84Coordinates.latitude << std::endl;
  os << std::setprecision(10);
  os << "latitude in degree :" << wgs84Coordinates.latitude * 180 / M_PI << std::endl;
  os << std::setprecision(10);
  os << "longitude in radian :" << wgs84Coordinates.longitude << std::endl;
  os << std::setprecision(10);
  os << "longitude in degree :" << wgs84Coordinates.longitude * 180 / M_PI << std::endl;
  return os;
}

}  // namespace romea
