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


#ifndef ROMEA_CORE_COMMON__GEODESY__ECEFCONVERTER_HPP_
#define ROMEA_CORE_COMMON__GEODESY__ECEFCONVERTER_HPP_

// Eigen
#include <Eigen/Core>

// romea
#include "romea_core_common/geodesy/GeodeticCoordinates.hpp"
#include "romea_core_common/geodesy/EarthEllipsoid.hpp"

namespace romea
{
namespace core
{

class ECEFConverter
{
public:
  explicit ECEFConverter(const EarthEllipsoid & earthEllipsoid = EarthEllipsoid::GRS80);

  Eigen::Vector3d toECEF(const GeodeticCoordinates & geodeticCoordinates)const;

  GeodeticCoordinates  toWGS84(const Eigen::Vector3d & ecefPosition)const;

protected:
  EarthEllipsoid ellipsoid_;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEODESY__ECEFCONVERTER_HPP_
