#ifndef ROMEA_CORE_COMMON_MATH_MATRIX_HPP_
#define ROMEA_CORE_COMMON_MATH_MATRIX_HPP_

// std
#include <iostream>

// Eigen
#include <Eigen/Core>

// romea
#include "romea_core_common/math/Algorithm.hpp"


namespace Eigen {
using Vector6d = Eigen::Matrix<double, 6, 1> ;
using Vector6f = Eigen::Matrix<float, 6, 1>;
using Matrix6d = Eigen::Matrix<double, 6, 6>;
using Matrix6f = Eigen::Matrix<float, 6, 6>;
}

namespace romea {

//-----------------------------------------------------------------------------
template<class MatrixType>
bool isPositiveSemiDefiniteMatrix(const MatrixType & matrix)
{
  if (matrix.rows() != matrix.cols())
    return false;

  for (int i = 0; i < matrix.rows(); ++i)
  {
    for (int j = i; j < matrix.cols(); ++j)
    {
      if (i == j)
      {
        if (matrix(i, j) < 0)
        {
          std::cout << matrix << std::endl;
          return false;
        }
      } else {
        if (!near(matrix(i, j), matrix(j, i), 0.000001))
        {
          std::cout << matrix << std::endl;
          return false;
        }
      }
    }
  }

  return true;
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Eigen::Matrix<Scalar, 3, 3> toSe2Covariance(const Eigen::Matrix<Scalar, 6, 6> & se3Covariance)
{
  Eigen::Matrix<Scalar, 3, 3> se2Covariance = Eigen::Matrix<Scalar, 3, 3>::Zero();
  se2Covariance.template block<2, 2>(0, 0)= se3Covariance.template block<2, 2>(0, 0);
  se2Covariance(0, 2) = se3Covariance(0, 5);
  se2Covariance(1, 2) = se3Covariance(1, 5);
  se2Covariance(2, 0) = se3Covariance(5, 0);
  se2Covariance(2, 1) = se3Covariance(5, 1);
  se2Covariance(2, 2) = se3Covariance(5, 5);
  return se2Covariance;
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Eigen::Matrix<Scalar, 6, 6> toSe3Covariance(const Eigen::Matrix<Scalar, 3, 3> & se2Covariance)
{

  Eigen::Matrix<Scalar, 6, 6> se3Covariance = Eigen::Matrix<Scalar, 6, 6>::Zero();
  se3Covariance.template block<2, 2>(0, 0)= se2Covariance.template block<2, 2>(0, 0);
  se3Covariance(0, 5) = se2Covariance(0, 2);
  se3Covariance(1, 5) = se2Covariance(1, 2);
  se3Covariance(5, 0) = se2Covariance(2, 0);
  se3Covariance(5, 1) = se2Covariance(2, 1);
  se3Covariance(5, 5) = se2Covariance(2, 2);
  return se3Covariance;
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_MATH_MATRIX_HPP_
