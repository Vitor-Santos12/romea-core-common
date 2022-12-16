// romea
#include "romea_core_common/geodesy/WGS84Coordinates.hpp"

// std
#include <cassert>
#include <cmath>
#include <iomanip>

namespace romea {

//--------------------------------------------------------------------------
WGS84Coordinates makeWGS84Coordinates(const double & latitude,
                                      const double & longitude)
{
  assert(latitude >= - M_PI_2 && latitude <= M_PI_2);
  assert(longitude >= - M_PI && longitude <= M_PI);
  return {latitude, longitude};
}

//--------------------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates)
{
  os <<std::setprecision(10)<< "latitude in radian :" << wgs84Coordinates.latitude << std::endl;
  os <<std::setprecision(10)<< "latitude in degree :" << wgs84Coordinates.latitude*180/M_PI << std::endl;
  os <<std::setprecision(10)<< "longitude in radian :" << wgs84Coordinates.longitude << std::endl;
  os <<std::setprecision(10)<< "longitude in degree :" << wgs84Coordinates.longitude*180/M_PI << std::endl;
  return os;
}

}  //namespace romea

