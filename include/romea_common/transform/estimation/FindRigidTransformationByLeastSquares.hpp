#ifndef romea_FindRigidTransformationByLeastSquares_hpp
#define romea_FindRigidTransformationByLeastSquares_hpp

//romea
#include "../../coordinates/CartesianCoordinates.hpp"
#include "../../coordinates/HomogeneousCoordinates.hpp"
#include "../../regression/leastsquares/LeastSquares.hpp"
#include "../../pointset/algorithms/PreconditionedPointSet.hpp"
#include "../../pointset/algorithms/Correspondence.hpp"
#include "../../pointset/NormalSet.hpp"

namespace romea {

template <class PointType>
class FindRigidTransformationByLeastSquares
{

public :

  using Scalar = typename PointType::Scalar ;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;


  using PreconditionedPointSetType= PreconditionedPointSet<PointType >;
  using TransformationMatrixType = Eigen::Matrix<Scalar,CARTESIAN_DIM +1,CARTESIAN_DIM +1>;

public :

  FindRigidTransformationByLeastSquares();

  TransformationMatrixType find(const PointSet<PointType> & sourcePoints,
                                const PointSet<PointType> & targetPoints,
                                const NormalSet<PointType> & targetPointsNormals);

  TransformationMatrixType find(const PreconditionedPointSetType & sourcePoints,
                                const PreconditionedPointSetType & targetPoints,
                                const NormalSet<PointType> & targetPointsNormals);


  TransformationMatrixType find(const PointSet<PointType> & sourcePoints,
                                const PointSet<PointType> & targetPoints,
                                const NormalSet<PointType> & targetPointsNormals,
                                const std::vector<Correspondence> & correspondences);

  TransformationMatrixType find(const PreconditionedPointSetType & sourcePoints,
                                const PreconditionedPointSetType & targetPoints,
                                const NormalSet<PointType> & targetPointsNormals,
                                const std::vector<Correspondence> & correspondences);

  void setPreconditioner(const PreconditionedPointSetType & sourcePoints,
                         const PreconditionedPointSetType & targetPoints);

private :

  TransformationMatrixType estimate_(const PointSet<PointType> &sourcePoints,
                                     const PointSet<PointType> &targetPoints,
                                     const NormalSet<PointType> & targetPointsNormals);

  TransformationMatrixType estimate_(const PointSet<PointType> &sourcePoints,
                                     const PointSet<PointType> &targetPoints,
                                     const NormalSet<PointType> & targetPointsNormals,
                                     const std::vector<Correspondence> &correspondences);

private :


  LeastSquares<Scalar> leastSquares_;

};

}

#endif

