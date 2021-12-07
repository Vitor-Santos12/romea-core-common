#include "romea_core_common/containers/grid/RayTracing.hpp"

namespace romea {


//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
RayCasting<Scalar, DIM>::RayCasting():
  RayCasting<Scalar, DIM>(nullptr)
{

}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
RayCasting<Scalar, DIM>::RayCasting(GridIndexMapping<Scalar,DIM> * gridIndexMapping):
  gridIndexMapping_(gridIndexMapping),
  rayOriginPoint_(PointType::Zero()),
  rayEndPoint_(PointType::Zero()),
  rayOriginIndexes_(CellIndexes::Zero()),
  rayEndIndexes_(CellIndexes::Zero()),
  rayTMax_(PointType::Zero()),
  rayTDelta_(PointType::Zero()),
  rayDirection_(PointType::Zero()),
  rayStep_(Eigen::Matrix<int,DIM,1>::Zero())
{

}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM> void
RayCasting<Scalar, DIM>::setGridIndexMapping(GridIndexMapping<Scalar,DIM> * gridIndexMapping)
{
  gridIndexMapping_ = gridIndexMapping;
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM> void
RayCasting<Scalar, DIM>::setOriginPoint(const PointType & originPoint)
{
  rayOriginPoint_ = originPoint ;
  rayOriginIndexes_ = gridIndexMapping_->computeCellIndexes(rayOriginPoint_);
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
const typename RayCasting<Scalar, DIM>::PointType &
RayCasting<Scalar, DIM>::getOriginPoint() const
{
  return rayOriginPoint_;
}


//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM> size_t
RayCasting<Scalar, DIM>::computeRayNumberOfCells()const
{
  return (rayEndIndexes_.template cast<int>() -
          rayOriginIndexes_.template cast<int>()).array().abs().sum()+1;
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
const typename RayCasting<Scalar, DIM>::PointType &
RayCasting<Scalar, DIM>::getEndPoint() const
{
  return rayEndPoint_;
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM> void
RayCasting<Scalar, DIM>::setEndPoint(const PointType &endPoint)
{
  rayEndPoint_ = endPoint;
  rayEndIndexes_ = gridIndexMapping_->computeCellIndexes(rayEndPoint_);

  PointType rayOriginCellCenterPosition = gridIndexMapping_->computeCellCenterPosition(rayOriginIndexes_);

  PointType direction = rayEndPoint_ - rayOriginPoint_;
  Scalar range = direction.norm();
  rayDirection_=direction/range;

  for(int i=0; i < static_cast<int>(DIM); ++i) {

    // compute step direction
    if (rayDirection_[i] > 0)
    {
      rayStep_[i] =  1;
    }
    else if (rayDirection_[i] < 0)
    {
      rayStep_[i] = -1;
    }
    else
    {
      rayStep_[i] = 0;
    }

    // compute rayTMax_, tDelta
    if (rayStep_[i] != 0) {

      // corner point of voxel (in direction of ray)
      Scalar voxelBorder = rayOriginCellCenterPosition[i];
      voxelBorder += (rayStep_[i] * gridIndexMapping_->getCellResolution() * Scalar(0.5));
      rayTMax_[i] =  ( voxelBorder - rayOriginPoint_[i])/ rayDirection_[i];
      rayTDelta_[i] = gridIndexMapping_->getCellResolution() / std::abs( rayDirection_[i] );
    }
    else {
      rayTMax_[i] =  std::numeric_limits<Scalar>::max( );
      rayTDelta_[i] = std::numeric_limits<Scalar>::max( );
    }
  }
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
const typename RayCasting<Scalar, DIM>::CellIndexes &
RayCasting<Scalar, DIM>::getOriginPointIndexes()const
{
  return  rayOriginIndexes_;
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
const typename RayCasting<Scalar, DIM>::CellIndexes &
RayCasting<Scalar, DIM>::getEndPointIndexes()const
{
  return  rayEndIndexes_;
}


//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
VectorOfEigenVector<typename RayCasting<Scalar, DIM>::CellIndexes>
RayCasting<Scalar, DIM>::cast(const PointType & endPoint)
{

  setEndPoint(endPoint);
  return cast();
}

//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
VectorOfEigenVector<typename RayCasting<Scalar, DIM>::CellIndexes>
RayCasting<Scalar, DIM>::cast()
{

  size_t rayNumberOfCells = computeRayNumberOfCells();
  VectorOfEigenVector<CellIndexes> ray(rayNumberOfCells);
  CellIndexes rayCurrentIndexes = rayOriginIndexes_ ;

  size_t n=0;
  ray[n]=rayCurrentIndexes;
  while(++n!=rayNumberOfCells)
  {
    next(rayCurrentIndexes);
    ray[n]= rayCurrentIndexes;
  }

  return ray;
}


//-----------------------------------------------------------------------------
template <typename Scalar , size_t DIM>
VectorOfEigenVector<typename RayCasting<Scalar, DIM>::CellIndexes>
RayCasting<Scalar, DIM>::cast(const PointType & originPoint,const PointType & endPoint)
{
  setOriginPoint(originPoint);
  return cast(endPoint);
}

//TODO factoriser en utilisant const expr if
//-----------------------------------------------------------------------------
template <>
void RayCasting<float,2>::next(CellIndexes & cellIndexes)
{

  // find minimum rayTMax_
  // increment current position
  if (rayTMax_[0] < rayTMax_[1]){
    cellIndexes[0]+=rayStep_[0];
    rayTMax_[0] += rayTDelta_[0];
  }
  else
  {
    cellIndexes[1]+=rayStep_[1];
    rayTMax_[1] += rayTDelta_[1];
  }
}

template <>
void RayCasting<double,2>::next(CellIndexes & cellIndexes)
{

  // find minimum rayTMax_
  // increment current position
  if (rayTMax_[0] < rayTMax_[1]){
    cellIndexes[0]+=rayStep_[0];
    rayTMax_[0] += rayTDelta_[0];
  }
  else
  {
    cellIndexes[1]+=rayStep_[1];
    rayTMax_[1] += rayTDelta_[1];
  }
}

template <>
void RayCasting<float,3>::next(CellIndexes & cellIndexes)
{


  // find minimum tMax:
  if (rayTMax_[0] < rayTMax_[1]){
    if (rayTMax_[0] < rayTMax_[2])
    {
      cellIndexes[0]+=rayStep_[0];
      rayTMax_[0] += rayTDelta_[0];
    }
    else
    {
      cellIndexes[2]+=rayStep_[2];
      rayTMax_[2] += rayTDelta_[2];
    }
  }
  else {
    if (rayTMax_[1] < rayTMax_[2])
    {
      cellIndexes[1]+=rayStep_[1];
      rayTMax_[1] += rayTDelta_[1];
    }
    else
    {
      cellIndexes[2]+=rayStep_[2];
      rayTMax_[2] += rayTDelta_[2];

    }
  }

}

template <>
void RayCasting<double, 3>::next(CellIndexes & cellIndexes)
{
  // find minimum tMax:
  if (rayTMax_[0] < rayTMax_[1]){
    if (rayTMax_[0] < rayTMax_[2])
    {
      cellIndexes[0]+=rayStep_[0];
      rayTMax_[0] += rayTDelta_[0];
    }
    else
    {
      cellIndexes[2]+=rayStep_[2];
      rayTMax_[2] += rayTDelta_[2];
    }
  }
  else {
    if (rayTMax_[1] < rayTMax_[2])
    {
      cellIndexes[1]+=rayStep_[1];
      rayTMax_[1] += rayTDelta_[1];
    }
    else
    {
      cellIndexes[2]+=rayStep_[2];
      rayTMax_[2] += rayTDelta_[2];

    }
  }

}

template class RayCasting<float,2>;
template class RayCasting<float,3>;
template class RayCasting<double,2>;
template class RayCasting<double,3>;

}
