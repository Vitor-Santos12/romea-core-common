#ifndef romea_RigidTransformationProjection_hpp
#define romea_RigidTransformationProjection_hpp

//romea
#include <romea_common/coordinates/CartesianCoordinates.hpp>
#include <romea_common/coordinates/HomogeneousCoordinates.hpp>

namespace romea {

//-----------------------------------------------------------------------------
template <typename Scalar>
void projection(const Eigen::Matrix<Scalar,3,3> & tranformationMatrix,
                const CartesianCoordinates2<Scalar> & sourcePoint,
                CartesianCoordinates2<Scalar> & targetPoint)
{
  targetPoint = tranformationMatrix.template block<2,2>(0,0)*sourcePoint +
      tranformationMatrix.template block<2,1>(0,2);
}

//-----------------------------------------------------------------------------
template <typename Scalar>
void projection(const Eigen::Matrix<Scalar,4,4> & tranformationMatrix,
                const CartesianCoordinates3<Scalar> & sourcePoint,
                CartesianCoordinates3<Scalar> & targetPoint)
{
  targetPoint = tranformationMatrix.template block<3,3>(0,0)*sourcePoint +
      tranformationMatrix.template block<3,1>(0,3);
}

//-----------------------------------------------------------------------------
template <typename Scalar>
void projection(const Eigen::Matrix<Scalar,3,3> & tranformationMatrix,
                const HomogeneousCoordinates2<Scalar> & sourcePoint,
                HomogeneousCoordinates2<Scalar> & targetPoint)
{
  targetPoint = tranformationMatrix *sourcePoint;
}

//-----------------------------------------------------------------------------
template <typename Scalar>
void projection(const Eigen::Matrix<Scalar,4,4> & tranformationMatrix,
                const HomogeneousCoordinates3<Scalar> & sourcePoint,
                HomogeneousCoordinates3<Scalar> & targetPoint)
{
  targetPoint = tranformationMatrix*sourcePoint;
}


}

#endif
