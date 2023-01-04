// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__POINTSET__KDTREE__NANOFLANNADAPTOR_HPP_
#define ROMEA_CORE_COMMON__POINTSET__KDTREE__NANOFLANNADAPTOR_HPP_

// std
#include <memory>

// romea
#include "romea_core_common/pointset/PointSet.hpp"
#include "romea_core_common/pointset/PointTraits.hpp"

// Flann
#include "romea_core_common/pointset/kdtree/nanoflann.hpp"


namespace romea
{

template<class PointType, class Distance = nanoflann::metric_L2>
struct NanoFlannAdaptor
{
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using SELF = NanoFlannAdaptor<PointType, Distance>;
  using METRIC = typename Distance::template traits<typename PointType::Scalar, SELF>::distance_t;
  using Index = nanoflann::KDTreeSingleIndexAdaptor<METRIC, SELF, POINT_SIZE, size_t>;

  const VectorOfEigenVector<PointType> & m_data;

  std::unique_ptr<Index> index;

  explicit NanoFlannAdaptor(const PointSet<PointType> & pointSet, const int & leafMaxSize = 10);

  explicit NanoFlannAdaptor(const NanoFlannAdaptor & flannKDTreeAdaptor) = delete;

  NanoFlannAdaptor & operator=(const NanoFlannAdaptor & flannKDTreeAdaptor) = delete;

  // Functions to ensure compatibility with nanoflann implementation
  // see in nanoflann.hpp for futher information
  template<class BBOX>
  bool kdtree_get_bbox(BBOX & /*bb*/) const;
  typename PointType::Scalar kdtree_get_pt(const size_t index, int dim) const;
  size_t kdtree_get_point_count() const;
};


//-----------------------------------------------------------------------------
template<class PointType, class Distance>
NanoFlannAdaptor<PointType, Distance>::NanoFlannAdaptor(
  const PointSet<PointType> & pointSet,
  const int & leafMaxSize)
: m_data(pointSet),
  index()
{
  index.reset(
    new Index(
      CARTESIAN_DIM, *this /* adaptor */,
      nanoflann::KDTreeSingleIndexAdaptorParams(leafMaxSize)));
  index->buildIndex();
}

//-----------------------------------------------------------------------------
template<class PointType, class Distance>
typename PointType::Scalar
NanoFlannAdaptor<PointType, Distance>::kdtree_get_pt(const size_t idx, int dim) const
{
  return m_data[idx][dim];
}

//-----------------------------------------------------------------------------
template<class PointType, class Distance>
size_t
NanoFlannAdaptor<PointType, Distance>::kdtree_get_point_count() const
{
  return m_data.size();
}

//-----------------------------------------------------------------------------
template<class PointType, class Distance>
template<class BBOX>
bool NanoFlannAdaptor<PointType, Distance>::kdtree_get_bbox(BBOX & /*bb*/) const
{
  return false;
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__POINTSET__KDTREE__NANOFLANNADAPTOR_HPP_
