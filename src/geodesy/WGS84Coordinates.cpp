//romea
#include "romea_common/geodesy/WGS84Coordinates.hpp"

//std
#include <cassert>
#include <cmath>
#include <iomanip>

namespace romea {


//--------------------------------------------------------------------------
WGS84Coordinates::WGS84Coordinates():
  WGS84Coordinates(0,0)
{
}

//--------------------------------------------------------------------------
WGS84Coordinates::WGS84Coordinates(double latitude,
                                   double longitude):
  latitude_(latitude),
  longitude_(longitude)
{
  assert(latitude >= - M_PI_2 && latitude <= M_PI_2);
  assert(longitude >= - M_PI && longitude <= M_PI);
}

//--------------------------------------------------------------------------
double WGS84Coordinates::getLatitude() const
{
  return latitude_;
}

//--------------------------------------------------------------------------
double WGS84Coordinates::getLongitude() const
{
  return longitude_;
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates)
{
  os <<std::setprecision(10)<< "latitude in radian :" << wgs84Coordinates.getLatitude() << std::endl;
  os <<std::setprecision(10)<< "latitude in degree :" << wgs84Coordinates.getLatitude()*180/M_PI << std::endl;
  os <<std::setprecision(10)<< "longitude in radian :" << wgs84Coordinates.getLongitude() << std::endl;
  os <<std::setprecision(10)<< "longitude in degree :" << wgs84Coordinates.getLongitude()*180/M_PI << std::endl;
  return os;
}

}

