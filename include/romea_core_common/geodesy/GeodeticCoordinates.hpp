#ifndef romea_GeodeticCoordinates_hpp
#define romea_GeodeticCoordinates_hpp

//romea
#include "WGS84Coordinates.hpp"

namespace romea {

struct GeodeticCoordinates : WGS84Coordinates
{
  double altitude;
};

GeodeticCoordinates makeGeodeticCoordinates(const WGS84Coordinates & wgs84Coordinates,
                                            const double &altitude);

GeodeticCoordinates makeGeodeticCoordinates(const double & latitude,
                                            const double & longitude,
                                            const double & altitude);

std::ostream & operator<<(std::ostream & os, const GeodeticCoordinates & geodeticCoordinates);

}

#endif
