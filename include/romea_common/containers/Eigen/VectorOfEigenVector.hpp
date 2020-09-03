#ifndef romea_VectorOfEigenVector_hpp
#define romea_VectorOfEigenVector_hpp

#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdVector>

namespace romea{

template< class EigenVectorType > using VectorOfEigenVector =
std::vector<EigenVectorType,Eigen::aligned_allocator<EigenVectorType> >;

using VectorOfEigenVector2d=VectorOfEigenVector<Eigen::Vector2d>;
using VectorOfEigenVector3d=VectorOfEigenVector<Eigen::Vector3d>;
using VectorOfEigenVector4d=VectorOfEigenVector<Eigen::Vector4d>;

using VectorOfEigenVector2f=VectorOfEigenVector<Eigen::Vector2f> ;
using VectorOfEigenVector3f=VectorOfEigenVector<Eigen::Vector3f>;
using VectorOfEigenVector4f=VectorOfEigenVector<Eigen::Vector4f> ;

}//romea
#endif
