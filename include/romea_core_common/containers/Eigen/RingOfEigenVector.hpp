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


#ifndef ROMEA_CORE_COMMON__CONTAINERS__EIGEN__RINGOFEIGENVECTOR_HPP_
#define ROMEA_CORE_COMMON__CONTAINERS__EIGEN__RINGOFEIGENVECTOR_HPP_

#include "romea_core_common/containers/Eigen/VectorOfEigenVector.hpp"

namespace romea
{

template<class EigenVectorType>
class RingOfEigenVector
{
public:
  explicit RingOfEigenVector(size_t ringSize);

  void append(const EigenVectorType & position);

  const EigenVectorType & operator[](size_t n) const;

  size_t size()const;

  void clear();

  VectorOfEigenVector<EigenVectorType> & get();

  const VectorOfEigenVector<EigenVectorType> & get()const;

  size_t ringIndex_;

private:
  size_t ringSize_;
  VectorOfEigenVector<EigenVectorType> ring_;
};


//-----------------------------------------------------------------------------
template<class EigenVectorType>
RingOfEigenVector<EigenVectorType>::RingOfEigenVector(size_t ringSize)
: ringSize_(ringSize),
  ringIndex_(-1),
  ring_()
{
  ring_.reserve(ringSize);
}

//-----------------------------------------------------------------------------
template<class EigenVectorType>
VectorOfEigenVector<EigenVectorType> & RingOfEigenVector<EigenVectorType>::get()
{
  return ring_;
}

//-----------------------------------------------------------------------------
template<class EigenVectorType>
const VectorOfEigenVector<EigenVectorType> & RingOfEigenVector<EigenVectorType>::get() const
{
  return ring_;
}

//-----------------------------------------------------------------------------
template<class EigenVectorType>
void RingOfEigenVector<EigenVectorType>::append(const EigenVectorType & position)
{
  ringIndex_ = (ringIndex_ + 1) % ringSize_;

  if (ring_.size() == ringSize_) {
    ring_[ringIndex_] = position;
  } else {
    ring_.push_back(position);
  }
}

//-----------------------------------------------------------------------------
template<class EigenVectorType>
void RingOfEigenVector<EigenVectorType>::clear()
{
  ring_.clear();
}

//-----------------------------------------------------------------------------
template<class EigenVectorType>
size_t RingOfEigenVector<EigenVectorType>::size()const
{
  return ring_.size();
}

//-----------------------------------------------------------------------------
template<class EigenVectorType>
const EigenVectorType & RingOfEigenVector<EigenVectorType>::operator[](size_t n) const
{
  return ring_[(ringIndex_ - n) % ring_.size()];
}


}  // namespace romea

#endif  // ROMEA_CORE_COMMON__CONTAINERS__EIGEN__RINGOFEIGENVECTOR_HPP_
