// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEODESY__ENUCONVERTER_HPP_
#define ROMEA_CORE_COMMON__GEODESY__ENUCONVERTER_HPP_

// Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

// romea
#include "romea_core_common/geodesy/GeodeticCoordinates.hpp"
#include "romea_core_common/geodesy/ECEFConverter.hpp"


namespace romea
{

class ENUConverter
{
public:
  ENUConverter();

  explicit ENUConverter(const GeodeticCoordinates & anchor);

  void setAnchor(const GeodeticCoordinates & anchor);

  const GeodeticCoordinates & getAnchor()const;

  bool isAnchored() const;

  void reset();

public:
  GeodeticCoordinates toWGS84(const Eigen::Vector3d & enuPosition)const;

  GeodeticCoordinates toWGS84(double xNorth, double yEast, double zDown) const;

  Eigen::Vector3d toECEF(const Eigen::Vector3d & enuPosition)const;

  Eigen::Vector3d toECEF(double xNorth, double yEast, double zDown) const;

  Eigen::Vector3d toENU(const GeodeticCoordinates & geodeticCoordinates);

  Eigen::Vector3d toENU(const WGS84Coordinates & wgs84Coordinates);

  Eigen::Vector3d toENU(const Eigen::Vector3d & ecefCoordinates)const;

  const Eigen::Affine3d & getEnuToEcefTransform()const;

private:
  ECEFConverter ecefConverter_;
  GeodeticCoordinates wgs84Anchor_;
  Eigen::Affine3d enu2ecef_;

  bool isAnchored_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEODESY__ENUCONVERTER_HPP_
