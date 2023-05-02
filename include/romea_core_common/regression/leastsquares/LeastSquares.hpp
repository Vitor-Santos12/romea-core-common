// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef ROMEA_CORE_COMMON__REGRESSION__LEASTSQUARES__LEASTSQUARES_HPP_
#define ROMEA_CORE_COMMON__REGRESSION__LEASTSQUARES__LEASTSQUARES_HPP_

// Eigen
#include <Eigen/Eigen>

namespace romea
{

template<typename RealType>
class LeastSquares
{
public:
  using Matrix = Eigen::Matrix<RealType, Eigen::Dynamic, Eigen::Dynamic>;
  using Vector = Eigen::Matrix<RealType, Eigen::Dynamic, 1>;

public:
  LeastSquares();

  explicit LeastSquares(const size_t & estimateSize);

  LeastSquares(const size_t & estimateSize, const size_t & dataSize);

  virtual ~LeastSquares() = default;

  void setEstimateSize(const size_t & dataSize);

  bool setDataSize(const size_t & dataSize);

public:
  Vector estimateUsingCholeskyDecomposition();

  Vector estimateUsingSVD();

  Vector weightedEstimate();

  Matrix computeEstimateCovariance(const RealType & dataVariance);

  void setPreconditionner(const Matrix & Ac, const Vector & Bc);

  void setPreconditionner(const Matrix & Ac);

public:
  Matrix & getJ();
  const Matrix & getJ()const;

  Vector & getY();
  const Vector & getY()const;

  Vector & getW();
  const Vector & getW()const;

private:
  void weightJAndY_();
  void computeJTJ_();
  void computeJTY_();

private:
  int dataSize_;
  int estimateSize_;

  Matrix Ac_;
  Vector Bc_;

  Matrix J_;
  Vector Y_;
  Vector W_;

  Matrix JtJ_;
  Matrix inverseJtJ_;
  Vector JtY_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__REGRESSION__LEASTSQUARES__LEASTSQUARES_HPP_
