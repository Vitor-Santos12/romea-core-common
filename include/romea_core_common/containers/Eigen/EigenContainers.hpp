#ifndef romea_EigenContainers_hpp
#define romea_EigenContainers_hpp

#include "DequeOfEigenVector.hpp"
#include "ListOfEigenVector.hpp"
#include "VectorOfEigenVector.hpp"

namespace romea {

//-----------------------------------------------------------------------------
template< class EigenContainerType>
typename EigenContainerType::value_type
min(const EigenContainerType & points)
{

  using PointType=typename EigenContainerType::value_type;

  PointType minimalCoordinates = PointType::Constant(std::numeric_limits<typename PointType::Scalar>::max());
  for(auto point : points)
  {
    minimalCoordinates = minimalCoordinates.min(point);
  }

  return minimalCoordinates;
}

//-----------------------------------------------------------------------------
template< class EigenContainerType>
typename EigenContainerType::value_type
max(const EigenContainerType & points)
{
  using PointType= typename EigenContainerType::value_type;

  PointType maximalCoordinates = PointType::Constant(-std::numeric_limits<typename PointType::Scalar>::max());
  for(auto point : points)
  {
    maximalCoordinates = maximalCoordinates.max(point);
  }

  return maximalCoordinates;
}

//-----------------------------------------------------------------------------
template< class EigenContainerType>
typename EigenContainerType::value_type
mean(const EigenContainerType & points)
{
  using PointType= typename EigenContainerType::value_type;

  PointType meanCoordinates = PointType::Zero();
  for(auto point : points)
  {
    meanCoordinates+=point;
  }
  meanCoordinates/= points.size();
  return meanCoordinates;
}

//-----------------------------------------------------------------------------
template< class EigenContainerType>
void transform(const EigenContainerType & sourcePoints,
               EigenContainerType & targetPoints,
               const Eigen::Matrix<typename EigenContainerType::value_type::Scalar,
               Eigen::internal::traits<typename EigenContainerType::value_type>::RowsAtCompileTime,
               Eigen::internal::traits<typename EigenContainerType::value_type>::RowsAtCompileTime>& rotation,
               const Eigen::Matrix<typename EigenContainerType::value_type::Scalar,
               Eigen::internal::traits<typename EigenContainerType::value_type>::RowsAtCompileTime,1>& translation)
{

  targetPoints.resize(sourcePoints.size());
  auto itSource = std::cbegin(sourcePoints);
  auto itTarget = std::begin(targetPoints);

  for(;itSource!=sourcePoints.end();++itSource,++itTarget)
  {
    (*itTarget)=rotation*(*itSource)+translation;
  }
}


}

#endif
