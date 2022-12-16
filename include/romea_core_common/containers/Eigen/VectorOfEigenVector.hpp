#ifndef ROMEA_CORE_COMMON_CONTAINERS_EIGEN_VECTOROFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON_CONTAINERS_EIGEN_VECTOROFEIGENVECTOR_HPP_

// std
#include <vector>

// eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdVector>

namespace romea{

template< class EigenVectorType > using VectorOfEigenVector =
std::vector<EigenVectorType, Eigen::aligned_allocator<EigenVectorType> >;

using VectorOfEigenVector2d = VectorOfEigenVector<Eigen::Vector2d>;
using VectorOfEigenVector3d = VectorOfEigenVector<Eigen::Vector3d>;
using VectorOfEigenVector4d = VectorOfEigenVector<Eigen::Vector4d>;

using VectorOfEigenVector2f = VectorOfEigenVector<Eigen::Vector2f> ;
using VectorOfEigenVector3f = VectorOfEigenVector<Eigen::Vector3f>;
using VectorOfEigenVector4f = VectorOfEigenVector<Eigen::Vector4f> ;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_EIGEN_VECTOROFEIGENVECTOR_HPP_
