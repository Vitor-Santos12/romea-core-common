#ifndef romea_ECEFConverter_hpp
#define romea_ECEFConverter_hpp

//romea
#include <Eigen/Core>
#include "GeodeticCoordinates.hpp"
#include "EarthEllipsoid.hpp"


namespace romea {

class ECEFConverter
{
public:

  ECEFConverter(const EarthEllipsoid & earthEllipsoid=EarthEllipsoid::GRS80);

  Eigen::Vector3d toECEF(const GeodeticCoordinates & geodeticCoordinates)const;

  GeodeticCoordinates  toWGS84(const Eigen::Vector3d & ecefPosition)const;

protected:

  EarthEllipsoid ellipsoid_;

};

}

#endif
