//romea
#include "romea_common/geodesy/ENUConverter.hpp"

//std
#include <cassert>
#include <cmath>

namespace romea {

//--------------------------------------------------------------------------
ENUConverter::ENUConverter():
  ecefConverter_(),
  wgs84Anchor_(),
  enu2ecef_(Eigen::Affine3d::Identity()),
  isAnchored_(false)
{

}

//--------------------------------------------------------------------------
ENUConverter::ENUConverter(const GeodeticCoordinates & anchor):
  ENUConverter()
{
  setAnchor(anchor);
}

//--------------------------------------------------------------------------
const GeodeticCoordinates &ENUConverter::getAnchor()const
{
  return wgs84Anchor_;
}

//--------------------------------------------------------------------------
bool ENUConverter::isAnchored() const
{
  return isAnchored_;
}

//--------------------------------------------------------------------------
void ENUConverter::setAnchor(const GeodeticCoordinates & anchor)
{

  //Set anchor
  wgs84Anchor_ = anchor;

  enu2ecef_.translation() = ecefConverter_.toECEF(wgs84Anchor_);

  // Rotation matrix giving attitude of tangent plane
  // Plane axis are East North Up
  double latitude  =anchor.latitude;
  double longitude =anchor.longitude;

  enu2ecef_.linear().col(0) << -std::sin(longitude), std::cos(longitude)  ,  0;
  enu2ecef_.linear().col(1) << -std::sin(latitude)*std::cos(longitude),-std::sin(latitude)*sin(longitude), cos(latitude);
  enu2ecef_.linear().col(2) << std::cos(latitude)*std::cos(longitude), std::cos(latitude)*sin(longitude), sin(latitude);


  isAnchored_ = true;

}

//--------------------------------------------------------------------------
Eigen::Vector3d ENUConverter::toECEF(const Eigen::Vector3d & enuPosition)const
{
  assert(isAnchored_);

  return enu2ecef_*enuPosition;
}


//--------------------------------------------------------------------------
Eigen::Vector3d ENUConverter::toECEF(double xNorth, double yEast, double zDown) const
{
  return toECEF((Eigen::Vector3d()<< xNorth,yEast,zDown).finished());
}


//--------------------------------------------------------------------------
GeodeticCoordinates ENUConverter::toWGS84(const Eigen::Vector3d & enuPosition)const
{
  return ecefConverter_.toWGS84(toECEF(enuPosition));
}

//--------------------------------------------------------------------------
GeodeticCoordinates ENUConverter::toWGS84(double xNorth, double yEast, double zDown)const
{
  return toWGS84((Eigen::Vector3d()<< xNorth,yEast,zDown).finished());
}

//--------------------------------------------------------------------------
Eigen::Vector3d ENUConverter::toENU(const  Eigen::Vector3d & ecefCoordinates)const
{
  assert(isAnchored_);

  return enu2ecef_.inverse()*ecefCoordinates;
}

//--------------------------------------------------------------------------
Eigen::Vector3d ENUConverter::toENU(const  GeodeticCoordinates & geodeticCoordinates)
{
  if(!isAnchored())
  {
    setAnchor(geodeticCoordinates);
  }

  return toENU(ecefConverter_.toECEF(geodeticCoordinates));
}

//--------------------------------------------------------------------------
Eigen::Vector3d ENUConverter::toENU(const  WGS84Coordinates & wgs84Coordinates)
{
  return toENU(makeGeodeticCoordinates(wgs84Coordinates,wgs84Anchor_.altitude));
}

//--------------------------------------------------------------------------
const Eigen::Affine3d & ENUConverter::getEnuToEcefTransform() const
{
  return enu2ecef_;
}

//--------------------------------------------------------------------------
void ENUConverter::reset()
{
  enu2ecef_ = Eigen::Affine3d::Identity();
  isAnchored_ = false;
}

}


