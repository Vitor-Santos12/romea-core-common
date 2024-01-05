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


#ifndef ROMEA_CORE_COMMON_GEODESY_WGS84COORDINATES_HPP_
#define ROMEA_CORE_COMMON_GEODESY_WGS84COORDINATES_HPP_

#include <ostream>

namespace romea
{
namespace core
{

struct WGS84Coordinates
{
  double latitude;
  double longitude;
};

WGS84Coordinates makeWGS84Coordinates(
  const double & latitude,
  const double & longitude);

std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates);

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON_GEODESY_WGS84COORDINATES_HPP_
