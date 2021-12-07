#ifndef romea_PointSetPreconditioner_hpp
#define romea_PointSetPreconditioner_hpp

//romea
#include "../PointSet.hpp"
#include "../PointTraits.hpp"

//Eigen
#include <unsupported/Eigen/MatrixFunctions>

namespace romea{

template <class PointType>
class PointSetPreconditioner{

public :

  using Scalar =typename PointType::Scalar ;
  static constexpr size_t CARTESIAN_DIM = PointTraits<PointType>::DIM;
  static constexpr size_t POINT_SIZE = PointTraits<PointType>::SIZE;

  using TranslationVector=Eigen::Matrix<Scalar,CARTESIAN_DIM,1> ;

public :

  PointSetPreconditioner();

  PointSetPreconditioner(const PointSet<PointType> & points);

  void compute(const PointSet<PointType> & points);

  const PointType & getPointSetMean()const;

  const PointType & getPointSetMin()const;

  const PointType & getPointSetMax()const;

  const Scalar & getScale()const;

  const TranslationVector & getTranslation() const;

private :

  Scalar scale_;
  TranslationVector translation_;

  PointType pointSetMean_;
  PointType pointSetMin_;
  PointType pointSetMax_;

public :

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF_VECTORIZABLE_FIXED_SIZE(Scalar,POINT_SIZE)

};

}
#endif