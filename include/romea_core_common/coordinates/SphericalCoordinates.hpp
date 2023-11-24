// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef ROMEA_CORE_COMMON__COORDINATES__SPHERICALCOORDINATES_HPP_
#define ROMEA_CORE_COMMON__COORDINATES__SPHERICALCOORDINATES_HPP_

#include "romea_core_common/coordinates/CartesianCoordinates.hpp"
#include "romea_core_common/coordinates/PolarCoordinates.hpp"

namespace romea
{
namespace core
{

template<typename Scalar>
class SphericalCoordinates : public PolarCoordinates<Scalar>
{
public:
  SphericalCoordinates(Scalar range, Scalar azimut, Scalar elevation)
  : PolarCoordinates<Scalar>(range, azimut),
    elevation_(elevation)
  {
  }

  virtual ~SphericalCoordinates() = default;


  const Scalar & getElevation()const
  {
    return elevation_;
  }

private:
  Scalar elevation_;
};


struct SphericalTransform
{
  template<typename Scalar>
  static Scalar range(const Scalar x, const Scalar & y, const Scalar & z)
  {
    return std::sqrt(x * x + y * y + z * z);
  }

  template<typename Scalar>
  static Scalar range(const CartesianCoordinates3<Scalar> & point)
  {
    return point.norm();
  }

  template<typename Scalar>
  static Scalar range(const HomogeneousCoordinates3<Scalar> & point)
  {
    return point.template segment<3>(0).norm();
  }

  template<typename Scalar>
  static Scalar azimut(const Scalar x, const Scalar & y)
  {
    return std::atan2(y, x);
  }

  template<typename Scalar>
  static Scalar azimut(const CartesianCoordinates3<Scalar> & point)
  {
    return std::atan2(point.y(), point.x());
  }

  template<typename Scalar>
  static Scalar azimut(const HomogeneousCoordinates3<Scalar> & point)
  {
    return std::atan2(point.y(), point.x());
  }


  template<typename Scalar>
  static Scalar elevation(const Scalar z, const Scalar & range)
  {
    return std::acos(z / range);
  }

  template<typename Scalar>
  static Scalar elevation(const Scalar x, const Scalar & y, const Scalar & z)
  {
    return elevation(z, range(x, y, z));
  }

  template<typename Scalar>
  static Scalar elevation(const CartesianCoordinates3<Scalar> & point)
  {
    return elevation(point.z(), point.norm());
  }

  template<typename Scalar>
  static Scalar elevation(const HomogeneousCoordinates3<Scalar> & point)
  {
    return elevation(point.z(), point.template segment<3>(0).norm());
  }

  template<typename Scalar>
  static Scalar x(const Scalar & range, const Scalar & azimut, const Scalar & elevation)
  {
    return range * std::cos(azimut) * std::sin(elevation);
  }

  template<typename Scalar>
  static Scalar x(const SphericalCoordinates<Scalar> & point)
  {
    return x(point.getRange(), point.getAzimut(), point.getElevation());
  }

  template<typename Scalar>
  static Scalar y(const Scalar & range, const Scalar & azimut, const Scalar & elevation)
  {
    return range * std::sin(azimut) * std::sin(elevation);
  }

  template<typename Scalar>
  static Scalar y(const SphericalCoordinates<Scalar> & point)
  {
    return y(point.getRange(), point.getAzimut(), point.getElevation());
  }

  template<typename Scalar>
  static Scalar z(const Scalar & range, const Scalar & elevation)
  {
    return range * std::cos(elevation);
  }

  template<typename Scalar>
  static Scalar z(const SphericalCoordinates<Scalar> & point)
  {
    return z(point.getRange(), point.getElevation());
  }
};

//-----------------------------------------------------------------------------
template<typename Scalar>
SphericalCoordinates<Scalar> toSpherical(const CartesianCoordinates3<Scalar> & point)
{
  double range = SphericalTransform::range(point);

  return SphericalCoordinates<Scalar>(
    range,
    SphericalTransform::azimut(point),
    SphericalTransform::elevation(point.z(), range));
}

//-----------------------------------------------------------------------------
template<typename Scalar>
SphericalCoordinates<Scalar> toSpherical(const HomogeneousCoordinates3<Scalar> & point)
{
  double range = SphericalTransform::range(point);

  return SphericalCoordinates<Scalar>(
    range,
    SphericalTransform::azimut(point),
    SphericalTransform::elevation(point.z(), range));
}


//-----------------------------------------------------------------------------
template<typename Scalar>
CartesianCoordinates3<Scalar> toCartesian(const SphericalCoordinates<Scalar> & point)
{
  return CartesianCoordinates3<Scalar>(
    SphericalTransform::x(point),
    SphericalTransform::y(point),
    SphericalTransform::z(point));
}

//-----------------------------------------------------------------------------
template<typename Scalar>
HomogeneousCoordinates3<Scalar> toHomogeneous(const SphericalCoordinates<Scalar> & point)
{
  return HomogeneousCoordinates3<Scalar>(
    SphericalTransform::x(point),
    SphericalTransform::y(point),
    SphericalTransform::z(point));
}

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__COORDINATES__SPHERICALCOORDINATES_HPP_
