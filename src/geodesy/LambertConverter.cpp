// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include "romea_core_common/geodesy/LambertConverter.hpp"

// std
#include <cmath>
#include <iostream>

namespace
{
const double EPSILON = 1e-12;
}

namespace romea
{

//-----------------------------------------------------------------------------
LambertConverter::LambertConverter(
  const SecantProjectionParameters & parameters,
  const EarthEllipsoid & ellipsoid)
: LambertConverter(computeProjectionParameters(parameters, ellipsoid), ellipsoid.e)
{
}

//-----------------------------------------------------------------------------
LambertConverter::LambertConverter(
  const TangentProjectionParameters & parameters,
  const EarthEllipsoid & ellipsoid)
: LambertConverter(computeProjectionParameters(parameters, ellipsoid), ellipsoid.e)
{
}

//-----------------------------------------------------------------------------
LambertConverter::LambertConverter(
  const ProjectionParameters & parameters,
  const double & e)
: LambertConverter(parameters.longitude0, parameters.n, parameters.c,
    parameters.xs, parameters.ys, e)
{
}

//-----------------------------------------------------------------------------
LambertConverter::LambertConverter(
  const double & longitude0,
  const double & n,
  const double & c,
  const double & xs,
  const double & ys,
  const double & e)
:  longitude0_(longitude0), n_(n), c_(c), xs_(xs), ys_(ys), e_(e)
{
}

//-----------------------------------------------------------------------------
Eigen::Vector2d LambertConverter::toLambert(const WGS84Coordinates & wgs84Coordinates)const
{
  const double & longitude = wgs84Coordinates.longitude;
  const double & latitude = wgs84Coordinates.latitude;
  double isolat = computeIsometricLatitude(latitude, e_);

  return Eigen::Vector2d(
    xs_ + c_ * std::exp(-n_ * isolat) * std::sin(n_ * (longitude - longitude0_)),
    ys_ - c_ * std::exp(-n_ * isolat) * std::cos(n_ * (longitude - longitude0_)));
}

//-----------------------------------------------------------------------------
WGS84Coordinates LambertConverter::toWGS84(const Eigen::Vector2d & position) const
{
  double rho = std::sqrt(std::pow(position.x() - xs_, 2) + std::pow(position.y() - ys_, 2));
  double theta = std::atan((position.x() - xs_) / (ys_ - position.y()));
  return{computeLatitude(-std::log(rho / c_) / n_, e_), longitude0_ + theta / n_};
}

//-----------------------------------------------------------------------------
double LambertConverter::computeIsometricLatitude(
  const double & latitude,
  const double & e)
{
  return std::log(
    std::tan((M_PI / 4) + (latitude / 2)) *
    std::pow((1 - e * std::sin(latitude)) / (1 + e * std::sin(latitude)), e / 2));
}

//-----------------------------------------------------------------------------
double LambertConverter::computeLatitude(
  const double & isometricLatitude,
  const double & e)
{
  double latitude = 2 * std::atan(std::exp(isometricLatitude)) - M_PI_2;
  for (;; ) {
    double previous_latitude = latitude;
    double alpha = std::pow((1 + e * std::sin(latitude)) / (1 - e * std::sin(latitude)), e / 2.);

    latitude = 2 * std::atan(alpha * std::exp(isometricLatitude)) - M_PI_2;
    if (std::abs(latitude - previous_latitude) < EPSILON) {
      break;
    }
  }

  return latitude;
}


//-----------------------------------------------------------------------------
double LambertConverter::computeGrandeNormal(
  const double & latitude,
  const double & a,
  const double & e)
{
  return a / (std::sqrt(1 - std::pow(e * std::sin(latitude), 2)));
}


//-----------------------------------------------------------------------------
LambertConverter::ProjectionParameters LambertConverter::computeProjectionParameters(
  const SecantProjectionParameters & parameters,
  const EarthEllipsoid & ellipsoid)
{
  double N1 = computeGrandeNormal(parameters.latitude1, ellipsoid.a, ellipsoid.e);
  double N2 = computeGrandeNormal(parameters.latitude2, ellipsoid.a, ellipsoid.e);
  double isolat0 = computeIsometricLatitude(parameters.latitude0, ellipsoid.e);
  double isolat1 = computeIsometricLatitude(parameters.latitude1, ellipsoid.e);
  double isolat2 = computeIsometricLatitude(parameters.latitude2, ellipsoid.e);
  double coslat1 = std::cos(parameters.latitude1);
  double coslat2 = std::cos(parameters.latitude2);

  double n = std::log((N2 * coslat2) / (N1 * coslat1)) / (isolat1 - isolat2);
  double c = N1 * coslat1 / n * std::exp(n * isolat1);

  double ys = parameters.y0;
  if (std::abs(parameters.latitude0 - M_PI_2) > 0.000000001) {
    ys += c * std::exp(-n * isolat0);
  }

  return {parameters.longitude0, n, c, parameters.x0, ys};
}

//-----------------------------------------------------------------------------
LambertConverter::ProjectionParameters LambertConverter::computeProjectionParameters(
  const TangentProjectionParameters & parameters,
  const EarthEllipsoid & ellipsoid)
{
  double N = computeGrandeNormal(parameters.latitude0, ellipsoid.a, ellipsoid.e);
  double cotlat = std::cos(parameters.latitude0) / std::sin(parameters.latitude0);
  double isolat = computeIsometricLatitude(parameters.latitude0, ellipsoid.e);

  double n = std::sin(parameters.latitude0);
  double C = parameters.k0 * N * cotlat * std::exp(n * isolat);
  double YS = parameters.y0 + parameters.k0 * N * cotlat;
  return {parameters.longitude0, n, C, parameters.x0, YS};
}

}  // namespace romea
