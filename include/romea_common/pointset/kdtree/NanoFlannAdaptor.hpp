#ifndef romea_KdTreeAdaptor_hpp
#define romea_KdTreeAdaptor_hpp

//romea
#include "../PointSet.hpp"
#include "../PointTraits.hpp"

//Flann
#include "nanoflann.hpp"

//std
#include <memory>

namespace romea {

template <class PointType, class Distance = nanoflann::metric_L2  >
struct NanoFlannAdaptor
{


  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using SELF =NanoFlannAdaptor<PointType,Distance>;
  using METRIC = typename Distance::template traits<typename PointType::Scalar,SELF >::distance_t;
  using Index = nanoflann::KDTreeSingleIndexAdaptor< METRIC,SELF,POINT_SIZE,size_t>;

  const VectorOfEigenVector<PointType> & m_data;

  std::unique_ptr<Index> index;


  NanoFlannAdaptor(const PointSet<PointType> &pointSet, const int &leafMaxSize = 10);

  NanoFlannAdaptor(const NanoFlannAdaptor & flannKDTreeAdaptor)=delete;

  NanoFlannAdaptor & operator=(const NanoFlannAdaptor & flannKDTreeAdaptor) =delete;

  //Functions to ensure compatibility with nanoflann implementation
  //see in nanoflann.hpp for futher information
  template <class BBOX> bool kdtree_get_bbox(BBOX & /*bb*/) const;
  typename PointType::Scalar kdtree_get_pt(const size_t index, int dim) const;
  size_t kdtree_get_point_count() const;

};


//-----------------------------------------------------------------------------
template <class PointType, class Distance>
NanoFlannAdaptor<PointType,Distance>::
NanoFlannAdaptor(const PointSet<PointType> &pointSet, const int &leafMaxSize):
  m_data(pointSet),
  index()
{
  index.reset(new Index( CARTESIAN_DIM, *this /* adaptor */, nanoflann::KDTreeSingleIndexAdaptorParams(leafMaxSize)));
  index->buildIndex();
}

//-----------------------------------------------------------------------------
template <class PointType, class Distance> typename PointType::Scalar
NanoFlannAdaptor<PointType,Distance>::kdtree_get_pt(const size_t idx, int dim) const {
  return m_data[idx][dim];
}

//-----------------------------------------------------------------------------
template <class PointType, class Distance> size_t
NanoFlannAdaptor<PointType,Distance>::kdtree_get_point_count() const {
  return m_data.size();
}

//-----------------------------------------------------------------------------
template <class PointType, class Distance> template <class BBOX>
bool NanoFlannAdaptor<PointType,Distance>::kdtree_get_bbox(BBOX & /*bb*/) const {
  return false;
}



}
#endif

