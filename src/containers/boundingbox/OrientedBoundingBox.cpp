//romea
#include "romea_core_common/containers/boundingbox/OrientedBoundingBox.hpp"

namespace romea{


//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM>
OrientedBoundingBox<Scalar,DIM>::OrientedBoundingBox():
  aabb_(),
  rotation_(RotationType::Identity())
{
}

//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM>
OrientedBoundingBox<Scalar,DIM>::OrientedBoundingBox(const PointType & centerPosition,
                                                     const PointType & halfWidthExtents,
                                                     const RotationType & rotationMatrix):
  aabb_(centerPosition,halfWidthExtents),
  rotation_(rotationMatrix)
{
}

//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM>
const typename OrientedBoundingBox<Scalar,DIM>::PointType &
OrientedBoundingBox<Scalar,DIM>::getCenterPosition()const
{
  return aabb_.getCenterPosition();
}

//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM>
const typename OrientedBoundingBox<Scalar,DIM>::PointType &
OrientedBoundingBox<Scalar,DIM>::getHalfWidthExtents()const
{
  return aabb_.getHalfWidthExtents();
}

//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM>
const typename OrientedBoundingBox<Scalar,DIM>::RotationType &
OrientedBoundingBox<Scalar,DIM>::getRotationMatrix()const
{
  return rotation_;
}

//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM> bool
OrientedBoundingBox<Scalar,DIM>::isInside(const PointType &point) const
{
  return ((rotation_.transpose()*(point-aabb_.getCenterPosition())).array().abs()<=aabb_.getHalfWidthExtents().array()).prod();
}

//-----------------------------------------------------------------------------
template <typename Scalar, size_t DIM>
typename OrientedBoundingBox<Scalar,DIM>::AABBType
OrientedBoundingBox<Scalar,DIM>::toAxisAlignedBoundingBox()const
{
  PointType aabbHalfWidthExtents = PointType::Zero();

  for(int n=0;n<static_cast<int>(DIM);n++)
  {
    aabbHalfWidthExtents.array() +=
        (rotation_.col(n)*aabb_.getHalfWidthExtents()(n)).array().abs();
  }

  return AABBType(aabb_.getCenterPosition(),aabbHalfWidthExtents);
}


template class OrientedBoundingBox<float,2>;
template class OrientedBoundingBox<float,3>;
template class OrientedBoundingBox<double,2>;
template class OrientedBoundingBox<double,3>;

}
