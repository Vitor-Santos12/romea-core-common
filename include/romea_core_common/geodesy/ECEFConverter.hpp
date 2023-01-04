// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEODESY__ECEFCONVERTER_HPP_
#define ROMEA_CORE_COMMON__GEODESY__ECEFCONVERTER_HPP_

// Eigen
#include <Eigen/Core>

// romea
#include "romea_core_common/geodesy/GeodeticCoordinates.hpp"
#include "romea_core_common/geodesy/EarthEllipsoid.hpp"

namespace romea
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

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEODESY__ECEFCONVERTER_HPP_
