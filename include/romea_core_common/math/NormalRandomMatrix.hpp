#ifndef ROMEA_CORE_COMMON_MATH_NORMALRANDOMMATRIX_HPP_
#define ROMEA_CORE_COMMON_MATH_NORMALRANDOMMATRIX_HPP_

#include "romea_core_common/math/NormalRandomMatrixGenerator.hpp"

namespace romea
{

template < typename Scalar, size_t DIM, class PRNG = std::mt19937 >
class NormalRandomMatrix
{
public :

  using MeanVector = Eigen::Matrix<Scalar, DIM, 1>;
  using CovarianceMatrix = Eigen::Matrix<Scalar, DIM, DIM>;
  using Matrix = Eigen::Matrix<Scalar, DIM, Eigen::Dynamic, StorageOrder>;

public :

  NormalRandomMatrix():
    generator_(),
    matrix_()
  {
  }

  NormalRandomMatrix(const size_t &cases ):
    generator_(),
    matrix_(Matrix::Zero(cases))
  {
  }

  void resize(const size_t & cases)
  {
    matrix_.resize(DIM, cases);
  }

  void draw(const MeanVector &mean, const CovarianceMatrix &cov)
  {
    generator_.fill(mean, cov, matrix_);
  }

  const Matrix & get() const
  {
    return matrix_;
  }

private :

  NormalRandomMatrixGenerator<Scalar, DIM, StorageOrder, PRNG> generator_;
  Matrix matrix_;

};


template < typename Scalar, int StorageOrder = Eigen::RowMajor, class PRNG = std::mt19937 >
class NormalRandomMatrix<Scalar, 1, StorageOrder, PRNG>
{
public :

  using Matrix = Eigen::Matrix<Scalar, 1, Eigen::Dynamic, StorageOrder>;

public :

  NormalRandomMatrix():
    generator_(),
    matrix_()
  {
  }

  NormalRandomMatrix(const size_t &cases):
    generator_(),
    matrix_(Matrix::Zero(cases))
  {
  }

  void resize(const size_t & cases)
  {
    matrix_.resize(1, cases);
  }

  void draw(const Scalar &mean, const Scalar &std)
  {
    generator_.fill(mean, std, matrix_);
  }

  const Matrix & get() const
  {
    return matrix_;
  }

private :
  NormalRandomMatrixGenerator<Scalar, 1, StorageOrder, PRNG> generator_;
  Matrix matrix_;
};

template <typename Scalar>
using NormalRandomMatrix2D = NormalRandomMatrix<Scalar, 2>;

template <typename Scalar>
using NormalRandomMatrix3d = NormalRandomMatrix<Scalar, 3>;

template <typename Scalar>
using NormalRandomVector = NormalRandomMatrix<Scalar, 1>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_MATH_NORMALRANDOMMATRIX_HPP_
