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
#include "romea_core_common/geodesy/ECEFConverter.hpp"
#include "romea_core_common/geodesy/EarthEllipsoid.hpp"

namespace
{
const double EPSILON = 1e-11;
}

namespace romea
{

//--------------------------------------------------------------------------
ECEFConverter::ECEFConverter(const EarthEllipsoid & earthEllipsoid)
: ellipsoid_(earthEllipsoid)
{
}

//--------------------------------------------------------------------------
Eigen::Vector3d ECEFConverter::toECEF(const GeodeticCoordinates & geodeticCoordinates) const
{
  const double longitude = geodeticCoordinates.longitude;
  const double latitude = geodeticCoordinates.latitude;
  const double altitude = geodeticCoordinates.altitude;

  Eigen::Vector3d ecef;
  const double N = ellipsoid_.a / (sqrt(1.0 - ellipsoid_.e2 * sin(latitude) * sin(latitude)));
  ecef[0] = (N + altitude) * cos(latitude) * cos(longitude);
  ecef[1] = (N + altitude) * cos(latitude) * sin(longitude);
  ecef[2] = (N * (1.0 - ellipsoid_.e2) + altitude) * sin(latitude);

  return ecef;
}

//--------------------------------------------------------------------------
GeodeticCoordinates ECEFConverter::toWGS84(const Eigen::Vector3d & ecefPosition) const
{
  const double X = ecefPosition[0];
  const double Y = ecefPosition[1];
  const double Z = ecefPosition[2];

  // Compute longitude
  const double norm = sqrt(X * X + Y * Y);
  double longitude = 2.0 * atan(Y / (X + norm));

  // Compute latitude
  double latitude =
    atan(Z / (norm * (1.0 - (ellipsoid_.a * ellipsoid_.e2 / sqrt(X * X + Y * Y + Z * Z)))));

  double delta = 1.0;
  while (delta > EPSILON) {
    double s2 = sin(latitude) * sin(latitude);
    const double eLatitude =
      atan(
      (Z / norm) /
      (1.0 -
      (ellipsoid_.a * ellipsoid_.e2 * cos(latitude) / (norm * sqrt(1.0 - ellipsoid_.e2 * s2)))));

    delta = fabs(eLatitude - latitude);
    latitude = eLatitude;
  }

  // Compute altitude
  double s2 = sin(latitude) * sin(latitude);
  double altitude = norm / cos(latitude) - ellipsoid_.a / sqrt(1.0 - ellipsoid_.e2 * s2);

  return makeGeodeticCoordinates(latitude, longitude, altitude);
}

}  // namespace romea
