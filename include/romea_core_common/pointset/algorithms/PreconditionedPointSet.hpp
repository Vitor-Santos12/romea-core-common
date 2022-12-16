#ifndef ROMEA_CORE_COMMON_POINTSET_ALGORITHMS_PRECONDITIONEDPOINTSET_HPP_ 
#define ROMEA_CORE_COMMON_POINTSET_ALGORITHMS_PRECONDITIONEDPOINTSET_HPP_ 

// romea
#include "romea_core_common/pointset/PointSet.hpp"
#include "romea_core_common/pointset/algorithms/PointSetPreconditioner.hpp"

namespace romea{

template <class PointType>
class PreconditionedPointSet{
public :

  using Scalar = typename PointType::Scalar;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using TranslationVector = Eigen::Matrix<Scalar, CARTESIAN_DIM, 1>;
  using ScaleMatrix = Eigen::Matrix<Scalar, CARTESIAN_DIM, CARTESIAN_DIM> ;
  using TransformationMatrix = Eigen::Matrix<Scalar, CARTESIAN_DIM+1, CARTESIAN_DIM+1> ;
  using PointSetPreconditionerType = PointSetPreconditioner<PointType> ;

public :

  PreconditionedPointSet();

  PreconditionedPointSet(const PointSet<PointType> & points,
                         const PointSetPreconditionerType & preconditioner);

  PreconditionedPointSet(const PointSet<PointType> & points,
                         const Scalar & preconditioningScale);

  PreconditionedPointSet(const PointSet<PointType> & points,
                         const Scalar & preconditioningScale,
                         const TranslationVector & preconditioningTranslation);

  void compute(const PointSet<PointType> & points,
               const PointSetPreconditionerType & preconditioner);

  void compute(const PointSet<PointType> & points,
               const Scalar & preconditioningScale);

  void compute(const PointSet<PointType> & points,
               const Scalar & preconditioningScale,
               const TranslationVector & preconditioningTranslation);


  const PointSet<PointType> & get()const;

  const TransformationMatrix & getPreconditioningMatrix() const;

private :

  void allocate_(const size_t &numberOfPoints);

private :

  PointSet<PointType> points_;
  TransformationMatrix preconditioningMatrix_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_POINTSET_ALGORITHMS_PRECONDITIONEDPOINTSET_HPP_ 
