#ifndef romea_AxisAlignedBoundingBox_hpp
#define romea_AxisAlignedBoundingBox_hpp

#include  "../../pointset/PointSet.hpp"
#include  "../../pointset/PointTraits.hpp"
#include  "../../math/Interval.hpp"

namespace romea {

template <typename Scalar, size_t DIM>
class AxisAlignedBoundingBox{

public :

  using PointType = Eigen::Matrix<Scalar,DIM,1>;
  using IntervalType = Interval<Scalar,DIM>;

public :

  AxisAlignedBoundingBox();

  AxisAlignedBoundingBox(const IntervalType & extremities);

  AxisAlignedBoundingBox(const PointType & centerPosition,
                         const PointType & halfWidthExtents);

  virtual ~AxisAlignedBoundingBox()=default;


public:

  const PointType & getCenterPosition()const;

  const PointType & getHalfWidthExtents()const;

  virtual IntervalType toInterval()const;

  virtual bool isInside(const PointType & point) const;


protected :

  PointType centerPosition_;
  PointType halfWidthExtents_;

public :

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF_VECTORIZABLE_FIXED_SIZE(Scalar,DIM)

};


typedef AxisAlignedBoundingBox<float,2> AxisAlignedBoundingBox2f;
typedef AxisAlignedBoundingBox<float,3> AxisAlignedBoundingBox3f;
typedef AxisAlignedBoundingBox<double,2> AxisAlignedBoundingBox2d;
typedef AxisAlignedBoundingBox<double,3> AxisAlignedBoundingBox3d;

}

#endif
