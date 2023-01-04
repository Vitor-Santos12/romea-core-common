// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEODESY__EARTHELLIPSOID_HPP_
#define ROMEA_CORE_COMMON__GEODESY__EARTHELLIPSOID_HPP_

namespace romea
{

class EarthEllipsoid
{
public:
  static EarthEllipsoid GRS80;

  EarthEllipsoid(double a, double b);

  double meridionalRadius(const double & latitude) const;

  double transversalRadius(const double & latitude) const;

  // half long axis
  double a;

  // half short axis
  double b;

  // squared excentricity
  double e2;

  // excentricity
  double e;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEODESY__EARTHELLIPSOID_HPP_
