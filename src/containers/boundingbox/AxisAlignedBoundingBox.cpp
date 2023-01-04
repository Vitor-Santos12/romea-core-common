// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// romea
#include "romea_core_common/containers/boundingbox/AxisAlignedBoundingBox.hpp"

namespace romea
{

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
AxisAlignedBoundingBox<Scalar, DIM>::AxisAlignedBoundingBox()
: AxisAlignedBoundingBox(PointType::Zero(), PointType::Zero())
{
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
AxisAlignedBoundingBox<Scalar, DIM>::AxisAlignedBoundingBox(const IntervalType & extremities)
: centerPosition_(extremities.center()),
  halfWidthExtents_(extremities.width() / 2.)
{
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
AxisAlignedBoundingBox<Scalar, DIM>::AxisAlignedBoundingBox(
  const PointType & centerPosition,
  const PointType & halfWidthExtents)
: centerPosition_(centerPosition),
  halfWidthExtents_(halfWidthExtents)
{
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
typename AxisAlignedBoundingBox<Scalar, DIM>::IntervalType
AxisAlignedBoundingBox<Scalar, DIM>::toInterval()const
{
  return {centerPosition_ - halfWidthExtents_, centerPosition_ + halfWidthExtents_};
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
const typename AxisAlignedBoundingBox<Scalar, DIM>::PointType &
AxisAlignedBoundingBox<Scalar, DIM>::getCenterPosition()const
{
  return centerPosition_;
}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
const typename AxisAlignedBoundingBox<Scalar, DIM>::PointType &
AxisAlignedBoundingBox<Scalar, DIM>::getHalfWidthExtents()const
{
  return halfWidthExtents_;
}


////-----------------------------------------------------------------------------
// template <typename Scalar, size_t DIM> double
// AxisAlignedBoundingBox<Scalar,DIM>::computeSquaredDistanceFromEdge(const PointType & point)const
//{
//  PointType absCenteredPoint = (point-centerPosition_).array().abs();
//  return ((absCenteredPoint.array()>halfWidthExtents_.array()).cast<double>()*
//          (absCenteredPoint.array()-halfWidthExtents_.array())).square().sum();

//}

////-----------------------------------------------------------------------------
// template <typename Scalar, size_t DIM> double
// AxisAlignedBoundingBox<Scalar,DIM>::computeDistanceFromEdge(const PointType & point)const
//{
//  return std::sqrt(computeSquaredDistanceFromEdge(point));

//}

//-----------------------------------------------------------------------------
template<typename Scalar, size_t DIM>
bool
AxisAlignedBoundingBox<Scalar, DIM>::isInside(const PointType & point) const
{
  return ((point - centerPosition_).array().abs() <= halfWidthExtents_.array()).all();
}


template class AxisAlignedBoundingBox<float, 2>;
template class AxisAlignedBoundingBox<float, 3>;
template class AxisAlignedBoundingBox<double, 2>;
template class AxisAlignedBoundingBox<double, 3>;

}  // namespace romea
