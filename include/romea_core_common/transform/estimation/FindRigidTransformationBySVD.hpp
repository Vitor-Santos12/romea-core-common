#ifndef romea_FindRigidTransformationBySVD_hpp
#define romea_FindRigidTransformationBySVD_hpp

//romea
#include "../../pointset/algorithms/PreconditionedPointSet.hpp"
#include "../../pointset/algorithms/Correspondence.hpp"

#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>

namespace romea {

template <class PointType>
class FindRigidTransformationBySVD {

public :

  using Scalar = typename PointType::Scalar ;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;


  using PreconditionedPointSetType=PreconditionedPointSet<PointType>;
  using TransformationMatrixType =Eigen::Matrix<Scalar,CARTESIAN_DIM +1,CARTESIAN_DIM +1>;

public :

  FindRigidTransformationBySVD();

  TransformationMatrixType find(const PreconditionedPointSetType &sourcePoints,
                                const PreconditionedPointSetType &targetPoints,
                                const std::vector<Correspondence> &correspondences);

  TransformationMatrixType find(const PointSet<PointType> &sourcePoints,
                                const PointSet<PointType> &targetPoints,
                                const std::vector<Correspondence> &correspondences);

  TransformationMatrixType find(const PreconditionedPointSetType &sourcePoints,
                                const PreconditionedPointSetType &targetPoints);

  TransformationMatrixType find(const PointSet<PointType> &sourcePoints,
                                const PointSet<PointType> &targetPoints);

private :

  TransformationMatrixType estimate_(const PointSet<PointType> &sourcePoints,
                                     const PointSet<PointType> &targetPoints,
                                     const std::vector<Correspondence> &correspondences);

  TransformationMatrixType estimate_(const PointSet<PointType> &sourcePoints,
                                     const PointSet<PointType> &targetPoints);

};

}

#endif

