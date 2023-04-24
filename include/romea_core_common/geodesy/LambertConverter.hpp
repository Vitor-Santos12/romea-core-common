// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__GEODESY__LAMBERTCONVERTER_HPP_
#define ROMEA_CORE_COMMON__GEODESY__LAMBERTCONVERTER_HPP_

// Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

// romea
#include "romea_core_common/geodesy/WGS84Coordinates.hpp"
#include "romea_core_common/geodesy/EarthEllipsoid.hpp"


namespace romea
{

class LambertConverter
{
public:
  struct SecantProjectionParameters
  {
    double longitude0;
    double latitude0;
    double latitude1;
    double latitude2;
    double x0;
    double y0;
  };

  struct TangentProjectionParameters
  {
    double latitude0;
    double longitude0;
    double k0;
    double x0;
    double y0;
  };

  struct ProjectionParameters
  {
    double longitude0;
    double n;
    double c;
    double xs;
    double ys;
  };

public:
  LambertConverter(
    const SecantProjectionParameters & parameters,
    const EarthEllipsoid & ellipsoid);

  LambertConverter(
    const TangentProjectionParameters & parameters,
    const EarthEllipsoid & ellipsoid);

  LambertConverter(
    const ProjectionParameters & parameters,
    const double & e);

  LambertConverter(
    const double & longitude0,
    const double & n,
    const double & c,
    const double & xs,
    const double & ys,
    const double & e);

public:
  Eigen::Vector2d toLambert(const WGS84Coordinates & wgs84Coordinates)const;

  WGS84Coordinates toWGS84(const Eigen::Vector2d & position) const;

public:
  static double computeLatitude(
    const double & isometricLatitude,
    const double & e);

  static double computeIsometricLatitude(
    const double & latitude,
    const double & e);

  static double computeGrandeNormal(
    const double & latitude,
    const double & a,
    const double & e);

  static ProjectionParameters computeProjectionParameters(
    const SecantProjectionParameters & parameters,
    const EarthEllipsoid & ellipsoid);

  static ProjectionParameters computeProjectionParameters(
    const TangentProjectionParameters & parameters,
    const EarthEllipsoid & ellipsoid);

private:
  double longitude0_;
  double n_;
  double c_;
  double xs_;
  double ys_;
  double e_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__GEODESY__LAMBERTCONVERTER_HPP_
