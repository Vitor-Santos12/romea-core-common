//romea
#include "romea_common/pointset/algorithms/PointSetPreconditioner.hpp"

namespace romea{


//-----------------------------------------------------------------------------
template <class PointType>
PointSetPreconditioner<PointType>::PointSetPreconditioner():
  scale_(0),
  translation_(TranslationVector::Zero()),
  pointSetMean_(PointType::Zero()),
  pointSetMin_(PointType::Zero()),
  pointSetMax_(PointType::Zero())
{
}

//-----------------------------------------------------------------------------
template <class PointType>
PointSetPreconditioner<PointType>::PointSetPreconditioner(const PointSet<PointType> & points):
  PointSetPreconditioner<PointType>::PointSetPreconditioner()
{
  compute(points);
}

//-----------------------------------------------------------------------------
template <class PointType> void
PointSetPreconditioner<PointType>::
compute(const PointSet<PointType> & points)
{

  //Compute mean and scales of point set
  pointSetMean_.setConstant(0);
  pointSetMin_.setConstant(std::numeric_limits<Scalar>::max());
  pointSetMax_.setConstant(std::numeric_limits<Scalar>::min());
  for(size_t n  = 0 , N = points.size();  n< N;++n){
    const PointType & point = points[n];
    pointSetMin_.array() = pointSetMin_.array().min(point.array());
    pointSetMax_.array() = pointSetMax_.array().max(point.array());
    pointSetMean_ += point;
  }
  pointSetMean_/=int(points.size());


  //Scale min, max and mean
  scale_ = 1/(pointSetMax_-pointSetMin_).maxCoeff();
  translation_ = -pointSetMean_.head(CARTESIAN_DIM) * scale_;
}

//-----------------------------------------------------------------------------
template <class PointType>
const PointType & PointSetPreconditioner<PointType>::getPointSetMean()const{
  return pointSetMean_;
}

//-----------------------------------------------------------------------------
template <class PointType>
const PointType & PointSetPreconditioner<PointType>::getPointSetMin()const
{
  return pointSetMin_;
}

//-----------------------------------------------------------------------------
template <class PointType>
const PointType & PointSetPreconditioner<PointType>::getPointSetMax()const
{
  return pointSetMax_;
}


//-----------------------------------------------------------------------------
template <class PointType> const typename PointType::Scalar &
PointSetPreconditioner<PointType>::getScale()const
{
  return scale_;
}

//-----------------------------------------------------------------------------
template <class PointType>
const typename PointSetPreconditioner<PointType>::TranslationVector &
PointSetPreconditioner<PointType>::getTranslation() const
{
  return translation_;
}

template class PointSetPreconditioner<Eigen::Vector2f>;
template class PointSetPreconditioner<Eigen::Vector2d>;
template class PointSetPreconditioner<Eigen::Vector3f>;
template class PointSetPreconditioner<Eigen::Vector3d>;

template class PointSetPreconditioner<HomogeneousCoordinates2f>;
template class PointSetPreconditioner<HomogeneousCoordinates2d>;
template class PointSetPreconditioner<HomogeneousCoordinates3f>;
template class PointSetPreconditioner<HomogeneousCoordinates3d>;

}
