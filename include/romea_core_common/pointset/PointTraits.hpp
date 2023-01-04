// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__POINTSET__POINTTRAITS_HPP_
#define ROMEA_CORE_COMMON__POINTSET__POINTTRAITS_HPP_

#include "romea_core_common/coordinates/CartesianCoordinates.hpp"
#include "romea_core_common/coordinates/HomogeneousCoordinates.hpp"

namespace romea
{


template<class PointType>
struct PointTraits
{
  static constexpr int DIM = 0;
  static constexpr int SIZE = 0;
};

template<>
struct PointTraits<CartesianCoordinates2f>
{
  static constexpr int DIM = 2;
  static constexpr int SIZE = 2;
};

template<>
struct PointTraits<CartesianCoordinates2d>
{
  static constexpr int DIM = 2;
  static constexpr int SIZE = 2;
};

template<>
struct PointTraits<CartesianCoordinates3f>
{
  static constexpr int DIM = 3;
  static constexpr int SIZE = 3;
};

template<>
struct PointTraits<CartesianCoordinates3d>
{
  static constexpr int DIM = 3;
  static constexpr int SIZE = 3;
};

template<>
struct PointTraits<HomogeneousCoordinates2f>
{
  static constexpr int DIM = 2;
  static constexpr int SIZE = 3;
};

template<>
struct PointTraits<HomogeneousCoordinates2d>
{
  static constexpr int DIM = 2;
  static constexpr int SIZE = 3;
};

template<>
struct PointTraits<HomogeneousCoordinates3f>
{
  static constexpr int DIM = 3;
  static constexpr int SIZE = 4;
};

template<>
struct PointTraits<HomogeneousCoordinates3d>
{
  static constexpr int DIM = 3;
  static constexpr int SIZE = 4;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__POINTTRAITS_HPP_
