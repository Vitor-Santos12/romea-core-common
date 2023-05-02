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


#ifndef ROMEA_CORE_COMMON__COORDINATES__POLARCOORDINATES_HPP_
#define ROMEA_CORE_COMMON__COORDINATES__POLARCOORDINATES_HPP_

#include "romea_core_common/coordinates/CartesianCoordinates.hpp"
#include "romea_core_common/coordinates/HomogeneousCoordinates.hpp"

namespace romea
{


//-----------------------------------------------------------------------------
template<typename Scalar>
class PolarCoordinates
{
public:
  PolarCoordinates(Scalar range, Scalar azimut)
  : range_(range),
    azimut_(azimut)
  {
  }

  virtual ~PolarCoordinates() = default;

public:
  const Scalar & getRange()const
  {
    return range_;
  }

  const Scalar & getAzimut()const
  {
    return azimut_;
  }

private:
  Scalar range_;
  Scalar azimut_;
};

//-----------------------------------------------------------------------------
struct PolarTransform
{
  template<typename Scalar>
  static Scalar azimut(const Scalar x, const Scalar & y)
  {
    return std::atan2(y, x);
  }

  template<typename Scalar>
  static Scalar azimut(const CartesianCoordinates2<Scalar> & point)
  {
    return std::atan2(point.y(), point.x());
  }

  template<typename Scalar>
  static Scalar azimut(const HomogeneousCoordinates2<Scalar> & point)
  {
    return std::atan2(point.y(), point.x());
  }

  template<typename Scalar>
  static Scalar range(const Scalar x, const Scalar & y)
  {
    return std::sqrt(x * x + y * y);
  }

  template<typename Scalar>
  static Scalar range(const CartesianCoordinates2<Scalar> & point)
  {
    return point.norm();
  }

  template<typename Scalar>
  static Scalar range(const HomogeneousCoordinates2<Scalar> & point)
  {
    return point.template segment<2>(0).norm();
  }

  template<typename Scalar>
  static Scalar x(const Scalar & range, const Scalar & azimut)
  {
    return range * std::cos(azimut);
  }

  template<typename Scalar>
  static Scalar x(const PolarCoordinates<Scalar> & point)
  {
    return x(point.getRange(), point.getAzimut());
  }

  template<typename Scalar>
  static Scalar y(const Scalar & range, const Scalar & azimut)
  {
    return range * std::sin(azimut);
  }

  template<typename Scalar>
  static Scalar y(const PolarCoordinates<Scalar> & point)
  {
    return y(point.getRange(), point.getAzimut());
  }
};


//-----------------------------------------------------------------------------
template<typename Scalar>
PolarCoordinates<Scalar> toPolar(const CartesianCoordinates2<Scalar> & point)
{
  return PolarCoordinates<Scalar>(
    PolarTransform::range(point),
    PolarTransform::azimut(point));
}

//-----------------------------------------------------------------------------
template<typename Scalar>
PolarCoordinates<Scalar> toHomogeneous(const HomogeneousCoordinates2<Scalar> & point)
{
  return PolarCoordinates<Scalar>(
    PolarTransform::range(point),
    PolarTransform::azimut(point));
}


//-----------------------------------------------------------------------------
template<typename Scalar>
CartesianCoordinates2<Scalar> toCartesian(const PolarCoordinates<Scalar> & point)
{
  return CartesianCoordinates2<Scalar>(
    PolarTransform::x(point),
    PolarTransform::y(point));
}

//-----------------------------------------------------------------------------
template<typename Scalar>
HomogeneousCoordinates2<Scalar> toHomogeneous(const PolarCoordinates<Scalar> & point)
{
  return HomogeneousCoordinates2<Scalar>(
    PolarTransform::x(point),
    PolarTransform::y(point));
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__COORDINATES__POLARCOORDINATES_HPP_
