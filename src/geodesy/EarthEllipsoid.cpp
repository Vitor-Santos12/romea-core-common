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


// std
#include <cmath>

// romea
#include "romea_core_common/geodesy/EarthEllipsoid.hpp"

namespace romea
{
namespace core
{

//--------------------------------------------------------------------------
EarthEllipsoid EarthEllipsoid::GRS80(6378137.0, 6356752.314);


//--------------------------------------------------------------------------
EarthEllipsoid::EarthEllipsoid(double A, double B)
: a(A),
  b(B),
  e2((a * a - b * b) / (a * a)),
  e(std::sqrt(e2))
{
}


//-----------------------------------------------------------------------------
double EarthEllipsoid::meridionalRadius(const double & latitude) const
{
  return a * (1 - e2) / (std::pow(1 - std::pow(e * std::sin(latitude), 2), 1.5));
}


//-----------------------------------------------------------------------------
double EarthEllipsoid::transversalRadius(const double & latitude) const
{
  return a * std::cos(latitude) / std::sqrt(1 - std::pow(e * std::sin(latitude), 2));
}

}  // namespace core
}  // namespace romea
