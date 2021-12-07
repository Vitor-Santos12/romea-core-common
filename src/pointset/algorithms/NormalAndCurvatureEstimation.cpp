//romea
#include "romea_core_common/pointset/algorithms/NormalAndCurvatureEstimation.hpp"

//stl
#include <cassert>

namespace {

//-----------------------------------------------------------------------------
template <typename PointType>
void flipNormalTowardOriginCoordinate(const PointType & point,PointType & normal)
{
  if(normal.dot(point/point.norm())>0)
  {
    normal*=-1;
  }
}

}

namespace romea{

//-----------------------------------------------------------------------------
template <class PointType>
NormalAndCurvatureEstimation<PointType>::
NormalAndCurvatureEstimation(const size_t & numberOfNeighborPoints):
  numberOfNeighborPoints_(numberOfNeighborPoints),
  neighborIndexes_(numberOfNeighborPoints_),
  neighborSquareDistances_(numberOfNeighborPoints_),
  eigenSolver_(),
  eigenValues_(EigenValuesType::Zero()),
  eigenVectors_(EigenVectorsType::Zero())
{

}

//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::
planeEstimation_(const PointSetType & points ,
                 const KdTreeType & pointsKdTree,
                 const size_t & pointIndex)
{
  using CovarianceMatrixType =Eigen::Matrix<Scalar,POINT_SIZE,POINT_SIZE>;

  pointsKdTree.findNearestNeighbors(points[pointIndex],
                                    numberOfNeighborPoints_,
                                    neighborIndexes_,
                                    neighborSquareDistances_);

  //    //Single passe covariance computation
  //    PointType mean = PointType::Zero();
  //    SquareMatrix covariance = SquareMatrix::Zero();

  //    for(size_t i=0;i<numberOfNeighborPoints_;++i){
  //      mean+=points[neighborIndexes[i]];
  //      covariance+=points[neighborIndexes[i]]*
  //          points[neighborIndexes[i]].transpose();
  //    }
  //    covariance -= mean*mean.transpose()/float(numberOfNeighborPoints_);
  //    covariance /= float(numberOfNeighborPoints_);


  //Two passes covariance computation
  PointType mean = PointType::Zero();
  for(size_t i=0;i<numberOfNeighborPoints_;++i)
    mean+=points[neighborIndexes_[i]];
  mean/= Scalar(numberOfNeighborPoints_);

  CovarianceMatrixType covariance = CovarianceMatrixType::Zero();
  for(size_t i=0;i<numberOfNeighborPoints_;++i)
    covariance +=(points[neighborIndexes_[i]]-mean)*
        (points[neighborIndexes_[i]]-mean).transpose();
  covariance /= Scalar(numberOfNeighborPoints_);

  eigenSolver_.compute(covariance.block(0,0,CARTESIAN_DIM,CARTESIAN_DIM));
  eigenValues_=eigenSolver_.eigenvalues();
  eigenVectors_=eigenSolver_.eigenvectors();

}

//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::compute(const PointSetType & points,
                                                 NormalSetType &normals)
{

  KdTree<PointType> pointsKdTree(points);
  compute(points,pointsKdTree,normals);
}

//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::compute(const PointSetType & points,
                                                 const KdTreeType & pointsKdTree,
                                                 NormalSetType & normals)
{

  assert(points.size() == normals.size());
  assert(numberOfNeighborPoints_ < points.size());

  for(size_t n=0, N=points.size(); n < N ;++n){

    planeEstimation_(points,pointsKdTree,n);
    std::copy(eigenVectors_.data(),eigenVectors_.data()+CARTESIAN_DIM,normals[n].data());
    flipNormalTowardOriginCoordinate(points[n],normals[n]);


  }
}

//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::compute(const PointSetType & points,
                                                 NormalSetType &normals,
                                                 VectorType & curvatures)
{

  KdTreeType pointsKdTree(points);
  compute(points,pointsKdTree,normals,curvatures);
}


//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::compute(const PointSetType & points,
                                                 const KdTreeType & pointsKdTree,
                                                 NormalSetType & normals,
                                                 VectorType & curvatures)
{

  assert(points.size() == normals.size());
  assert(numberOfNeighborPoints_ < points.size());


  for(size_t n=0, N=points.size(); n < N ;++n){

    planeEstimation_(points,pointsKdTree,n);
    curvatures[n] = eigenValues_(0)/ eigenValues_.array().sum();
    std::copy(eigenVectors_.data(),eigenVectors_.data()+CARTESIAN_DIM,normals[n].data());
    flipNormalTowardOriginCoordinate(points[n],normals[n]);
  }
}

//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::compute(const PointSetType & points,
                                                 NormalSetType &normals,
                                                 VectorType & curvatures,
                                                 VectorType & normalsReliability)
{

  KdTreeType pointsKdTree(points);
  compute(points,pointsKdTree,normals,curvatures,normalsReliability);
}

//TODO a factoriser en utilisant if constexpr en fonction de PointType::DIM
//-----------------------------------------------------------------------------
template <>
float NormalAndCurvatureEstimation<Eigen::Vector2f>::computeNormalReliability()
{
  return std::abs(eigenValues_(1)/eigenValues_(0));
}

//-----------------------------------------------------------------------------
template <>
double NormalAndCurvatureEstimation<Eigen::Vector2d>::computeNormalReliability()
{
  return std::abs(eigenValues_(1)/eigenValues_(0));
}

//-----------------------------------------------------------------------------
template <>
float NormalAndCurvatureEstimation<Eigen::Vector3f>::computeNormalReliability()
{
  return std::abs(std::min(eigenValues_(1),eigenValues_(2))/eigenValues_(0));
}

//-----------------------------------------------------------------------------
template <>
double NormalAndCurvatureEstimation<Eigen::Vector3d>::computeNormalReliability()
{
  return std::abs(std::min(eigenValues_(1),eigenValues_(2))/eigenValues_(0));
}

//-----------------------------------------------------------------------------
template <>
double NormalAndCurvatureEstimation<HomogeneousCoordinates2d>::computeNormalReliability()
{
  return std::abs(eigenValues_(1)/eigenValues_(0));
}


//-----------------------------------------------------------------------------
template <>
float NormalAndCurvatureEstimation<HomogeneousCoordinates2f>::computeNormalReliability()
{
  return std::abs(eigenValues_(1)/eigenValues_(0));
}

//-----------------------------------------------------------------------------
template <>
float NormalAndCurvatureEstimation<HomogeneousCoordinates3f>::computeNormalReliability()
{
  return std::abs(std::min(eigenValues_(1),eigenValues_(2))/eigenValues_(0));
}


//-----------------------------------------------------------------------------
template <>
double NormalAndCurvatureEstimation<HomogeneousCoordinates3d>::computeNormalReliability()
{
  return std::abs(std::min(eigenValues_(1),eigenValues_(2))/eigenValues_(0));
}


//-----------------------------------------------------------------------------
template <class PointType> void
NormalAndCurvatureEstimation<PointType>::compute(const PointSetType & points,
                                                 const KdTreeType & pointsKdTree,
                                                 NormalSetType &normals,
                                                 VectorType & curvatures,
                                                 VectorType & normalsReliability)
{

  assert(points.size() == normals.size());
  assert(numberOfNeighborPoints_ < points.size());

  for(size_t n=0, N=points.size(); n < N ;++n){

    planeEstimation_(points,pointsKdTree,n);
    curvatures[n] = eigenValues_(0)/ eigenValues_.array().sum();
    std::copy(eigenVectors_.data(),eigenVectors_.data()+CARTESIAN_DIM,normals[n].data());
    flipNormalTowardOriginCoordinate(points[n],normals[n]);
    normalsReliability[n] =computeNormalReliability();

  }

}

template class NormalAndCurvatureEstimation<Eigen::Vector2f>;
template class NormalAndCurvatureEstimation<Eigen::Vector2d>;
template class NormalAndCurvatureEstimation<Eigen::Vector3f>;
template class NormalAndCurvatureEstimation<Eigen::Vector3d>;

template class NormalAndCurvatureEstimation<HomogeneousCoordinates2f>;
template class NormalAndCurvatureEstimation<HomogeneousCoordinates2d>;
template class NormalAndCurvatureEstimation<HomogeneousCoordinates3f>;
template class NormalAndCurvatureEstimation<HomogeneousCoordinates3d>;

}



