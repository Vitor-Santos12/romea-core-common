#ifndef romea_WGS84Coordinates_hpp
#define romea_WGS84Coordinates_hpp

//std
#include <ostream>

namespace romea {

class WGS84Coordinates
{
public:

  WGS84Coordinates();

  WGS84Coordinates(double latitude,
                   double longitude);

  double getLatitude() const;
  double getLongitude() const;

protected :

  double latitude_;
  double longitude_;

};

std::ostream & operator<<(std::ostream & os, const WGS84Coordinates & wgs84Coordinates);

}

#endif
