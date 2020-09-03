#ifndef _romea_EarthEllipsoid_hpp_
#define _romea_EarthEllipsoid_hpp_

namespace romea {

class EarthEllipsoid
{
public:

  static EarthEllipsoid GRS80;

  EarthEllipsoid(double a, double b);

  double meridionalRadius(const double &latitude) const;

  double transversalRadius(const double &latitude) const;

  //half long axis
  double a;

  //half short axis
  double b;

  //squared excentricity
  double e2;

  //excentricity
  double e;


};

}

#endif
