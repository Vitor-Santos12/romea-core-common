//romea
#include "romea_common/geodesy/GeodeticCoordinates.hpp"


namespace romea {

//--------------------------------------------------------------------------
GeodeticCoordinates::GeodeticCoordinates():
  WGS84Coordinates(0,0),
  altitude_(0)
{

}

//--------------------------------------------------------------------------
GeodeticCoordinates::GeodeticCoordinates(double latitude,
                                         double longitude,
                                         double altitude):
  WGS84Coordinates(latitude,longitude),
  altitude_(altitude)
{

}

//--------------------------------------------------------------------------
GeodeticCoordinates::GeodeticCoordinates(const WGS84Coordinates & wgs84Coordinates,
                                         double altitude):
  WGS84Coordinates(wgs84Coordinates),
  altitude_(altitude)
{

}

//--------------------------------------------------------------------------
double GeodeticCoordinates::getAltitude() const
{
  return altitude_;
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const GeodeticCoordinates & geodeticCoordinates)
{
  os << static_cast<WGS84Coordinates>(geodeticCoordinates);
  os << "altitude in meter" << geodeticCoordinates.getAltitude();
  return os;
}

}

