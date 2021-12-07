//romea
#include "romea_core_common/geodesy/EarthEllipsoid.hpp"

//std
#include <cmath>

namespace romea {

//--------------------------------------------------------------------------
EarthEllipsoid EarthEllipsoid::GRS80(6378137.0, 6356752.314);


//--------------------------------------------------------------------------
EarthEllipsoid::EarthEllipsoid(double A, double B):
  a (A),
  b (B),
  e2 ((a*a - b*b) / (a*a)),
  e (std::sqrt(e2))
{

}


//-----------------------------------------------------------------------------
double EarthEllipsoid::meridionalRadius(const double &latitude) const
{
  return a*(1-e2)/(std::pow(1-std::pow(e*std::sin(latitude),2),1.5));
}


//-----------------------------------------------------------------------------
double EarthEllipsoid::transversalRadius(const double &latitude) const
{
  return a*std::cos(latitude)/std::sqrt(1-std::pow(e*std::sin(latitude),2));
}



}
