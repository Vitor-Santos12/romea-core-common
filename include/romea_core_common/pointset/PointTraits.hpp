#ifndef romea_PointTraits_hpp
#define romea_PointTraits_hpp

#include "../coordinates/CartesianCoordinates.hpp"
#include "../coordinates/HomogeneousCoordinates.hpp"

namespace romea {


template <class PointType>
struct PointTraits
{
  static constexpr int DIM=0;
  static constexpr int SIZE=0;
};

template <>
struct PointTraits<CartesianCoordinates2f>
{
  static constexpr int DIM=2;
  static constexpr int SIZE=2;
};

template <>
struct PointTraits<CartesianCoordinates2d>
{
  static constexpr int DIM=2;
  static constexpr int SIZE=2;
};

template <>
struct PointTraits<CartesianCoordinates3f>
{
  static constexpr int DIM=3;
  static constexpr int SIZE=3;
};

template <>
struct PointTraits<CartesianCoordinates3d>
{
  static constexpr int DIM=3;
  static constexpr int SIZE=3;
};

template <>
struct PointTraits<HomogeneousCoordinates2f>
{
  static constexpr int DIM=2;
  static constexpr int SIZE=3;
};

template <>
struct PointTraits<HomogeneousCoordinates2d>
{
  static constexpr int DIM=2;
  static constexpr int SIZE=3;
};

template <>
struct PointTraits<HomogeneousCoordinates3f>
{
  static constexpr int DIM=3;
  static constexpr int SIZE=4;
};

template <>
struct PointTraits<HomogeneousCoordinates3d>
{
  static constexpr int DIM=3;
  static constexpr int SIZE=4;
};


}

#endif
