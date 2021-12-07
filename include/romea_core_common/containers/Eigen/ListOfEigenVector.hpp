#ifndef romea_VectorOfEigenVector_hpp
#define romea_VectorOfEigenVector_hpp

#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdList>

namespace romea{

template< class EigenVectorType > using ListOfEigenVector =
std::list<EigenVectorType,Eigen::aligned_allocator<EigenVectorType> >;

}//romea
#endif
