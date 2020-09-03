#ifndef romea_GeodeticCoordinates_hpp
#define romea_GeodeticCoordinates_hpp

//romea
#include "WGS84Coordinates.hpp"

namespace romea {

class GeodeticCoordinates : public WGS84Coordinates
{
public:


  GeodeticCoordinates();

  GeodeticCoordinates(double latitude,
                      double longitude,
                      double altitude);

  GeodeticCoordinates(const WGS84Coordinates & wgs84Coordinates,
                      double altitude);

  double getAltitude() const;

protected :

  double altitude_;

};

std::ostream & operator<<(std::ostream & os, const GeodeticCoordinates & geodeticCoordinates);

}

#endif
