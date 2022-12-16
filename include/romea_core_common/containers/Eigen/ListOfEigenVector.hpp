#ifndef ROMEA_CORE_COMMON_CONTAINERS_EIGEN_LISTOFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON_CONTAINERS_EIGEN_LISTOFEIGENVECTOR_HPP_

// std
#include <list>

// Eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdList>

namespace romea{

template< class EigenVectorType > using ListOfEigenVector =
std::list<EigenVectorType, Eigen::aligned_allocator<EigenVectorType> >;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_EIGEN_LISTOFEIGENVECTOR_HPP_
