#ifndef ROMEA_CORE_COMMON_MATH_NORMALRANDOMMATRIXGENERATOR_HPP_
#define ROMEA_CORE_COMMON_MATH_NORMALRANDOMMATRIXGENERATOR_HPP_

// std
#include <utility>
#include <limits>
#include <random>
#include <cassert>
#include <iostream>

// Eigen
#include <Eigen/Core>
#include <Eigen/Cholesky>
#include <Eigen/Eigenvalues>

namespace romea
{

template < typename Scalar, size_t DIM, template <class > class ContainerBase = Eigen::MatrixBase, class PRNG = std::mt19937>
class NormalRandomMatrixGenerator
{
public :

  using MeanVector = Eigen::Matrix<Scalar, DIM, 1>;
  using CovarianceMatrix = Eigen::Matrix<Scalar, DIM, DIM>;
  using TransformMatrix = Eigen::Matrix<Scalar, DIM, DIM>;

public :

  NormalRandomMatrixGenerator():
//    engine_(std::random_device{}()),
    engine_(0),
    mean_(MeanVector::Zero()),
    covariance_(CovarianceMatrix::Zero()),
    transform_(TransformMatrix::Zero())
  {
  }

  void init(const MeanVector & mean, const CovarianceMatrix & covariance)
  {
    mean_ = mean;
    covariance_ = covariance;
    transform_ = covariance.llt().matrixL();
  }


  template <class Derived>
  void fill(ContainerBase<Derived> & container)
  {
    std::normal_distribution<Scalar> distribution(0, 1);
    //    container.unaryExpr([&](double /*dummy*/){return distribution(engine_);});

    for (int i = 0;  i< int(DIM); ++i)
    {
      for (int j = 0; j < container.cols(); ++j)
      {
        container(i, j) = distribution(engine_);
      }
    }

    //todo using constexpr if with c++17
    //    if(Eigen::internal::traits<Derived>::Options== Eigen::ColMajor)
    //    {
    //      container.matrix() = (transform_*container.matrix()).colwise()+mean_;
    //    }
    //    else
    //    {

    for (int i = DIM-1; i >= 0; --i)
    {
      container.row(i) = transform_(i, i)*container.row(i)+mean_(i);
      for (int j = i-1; j >= 0; --j)
      {
        container.row(i)+=transform_(i, j)*container.row(j);
      }
    }
  }

private :

  PRNG engine_;
  MeanVector mean_;
  CovarianceMatrix covariance_;

  TransformMatrix transform_;
};


template < typename Scalar, template <class > class ContainerBase , class PRNG>
class NormalRandomMatrixGenerator<Scalar, 1, ContainerBase, PRNG>
{
public :
  NormalRandomMatrixGenerator():
    engine_(std::random_device{}()),
    mean_(0),
    std_(0)
  {
  }

  void init(const Scalar & mean, const Scalar & std)
  {
    mean_ = mean;
    std_ = std;
  }

  template <class Derived>
  void fill(ContainerBase<Derived> & matrix)
  {
    std::normal_distribution<double> distribution(mean_, std_);
    matrix.unaryExpr([&](double /*dummy*/){return distribution(engine_);});
  }

private :

  PRNG engine_;
  Scalar mean_;
  Scalar std_;
};

template <typename Scalar>
using NormalRandomMatrixGenerator2D = NormalRandomMatrixGenerator<Scalar, 2, Eigen::MatrixBase>;

template <typename Scalar>
using NormalRandomMatrixGenerator3D = NormalRandomMatrixGenerator<Scalar, 3, Eigen::MatrixBase>;

template <typename Scalar>
using NormalRandomVectorGenerator = NormalRandomMatrixGenerator<Scalar, 1, Eigen::MatrixBase>;

template <typename Scalar>
using NormalRandomArrayGenerator2D = NormalRandomMatrixGenerator<Scalar, 2, Eigen::ArrayBase>;

template <typename Scalar>
using NormalRandomArrayGenerator3D = NormalRandomMatrixGenerator<Scalar, 3, Eigen::ArrayBase>;

template <typename Scalar>
using NormalRandomArrayGenerator = NormalRandomMatrixGenerator<Scalar, 1, Eigen::ArrayBase>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_MATH_NORMALRANDOMMATRIXGENERATOR_HPP_
