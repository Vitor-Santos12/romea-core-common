#ifndef romea_WGS84Coordinates_hpp
#define romea_WGS84Coordinates_hpp

//std
#include <ostream>

namespace romea {

struct WGS84Coordinates
{
  double latitude;
  double longitude;
};

WGS84Coordinates makeWGS84Coordinates(const double & latitude,
                                      const double & longitude);

std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates);

}

#endif
