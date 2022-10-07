#ifndef romea_Transformation_hpp
#define romea_Transformation_hpp

//Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace romea {

  //-----------------------------------------------------------------------------
  template <typename Scalar>
  inline Eigen::Transform<Scalar,3,Eigen::Affine> rigid_transformation3(
    const Eigen::Matrix<Scalar,3,1> & translation,
    const Eigen::Matrix<Scalar,3,1> & angles)
  {
   using EigenVector = Eigen::Matrix<Scalar,3,1>;
   using EigenAngleAxis = Eigen::AngleAxis<Scalar>;
   using EigenTransform = Eigen::Transform<Scalar,3,Eigen::Affine>;

   EigenTransform rigidTransformation = EigenTransform::Identity();
   rigidTransformation.rotate(EigenAngleAxis(angles[0],EigenVector::UnitX()));
   rigidTransformation.rotate(EigenAngleAxis(angles[1], EigenVector::UnitY()));
   rigidTransformation.rotate(EigenAngleAxis(angles[2], EigenVector::UnitZ()));
   rigidTransformation.translate(translation);
   return rigidTransformation;
  }
}//romea

#endif
