#ifndef ROMEA_CORE_COMMON_CONTAINERS_EIGEN_DEQUEOFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON_CONTAINERS_EIGEN_DEQUEOFEIGENVECTOR_HPP_

// std
#include <vector>

// eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/StdDeque>

namespace romea{

template< class EigenVectorType > using DequeOfEigenVector =
std::vector<EigenVectorType, Eigen::aligned_allocator<EigenVectorType> >;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_EIGEN_DEQUEOFEIGENVECTOR_HPP_
