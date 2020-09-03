#ifndef romea_DequeOfEigenVector_hpp
#define romea_DequeOfEigenVector_hpp

#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdDeque>

namespace romea{

template< class EigenVectorType > using DequeOfEigenVector =
std::vector<EigenVectorType,Eigen::aligned_allocator<EigenVectorType> >;

}//romea
#endif
