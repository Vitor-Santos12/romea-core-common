#ifndef romea_KdTree_hpp
#define romea_KdTree_hpp


//romea
#include "kdtree/NanoFlannAdaptor.hpp"
#include "PointTraits.hpp"

namespace romea{

template <class PointType >
class KdTree{

public :

  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

public :

  KdTree(const PointSet<PointType> &points);

  void findNearestNeighbor(const PointType &point,
                           size_t & neighboorIndex,
                           Scalar & neighboorSquareDistance)const;

  void findNearestNeighbors(const PointType &point,
                            const size_t &numberOfNeighbors,
                            std::vector<size_t> &neighboorIndexes,
                            std::vector<Scalar> &neighboorSquareDistances)const;

  void radiusResearch(const PointType & point,
                      const Scalar & radius,
                      std::vector<size_t> & neighboorIndexes,
                      std::vector<Scalar> & neighboorSquareDistances);
public :


  NanoFlannAdaptor<PointType,nanoflann::metric_L2 >  kdtree_;

  mutable nanoflann::KNNResultSet<Scalar> singleNNResult_;
};

}
#endif


