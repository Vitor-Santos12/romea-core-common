#ifndef ROMEA_CORE_COMMON_POINTSET_NORMALSET_HPP_
#define ROMEA_CORE_COMMON_POINTSET_NORMALSET_HPP_

#include "../containers/Eigen/VectorOfEigenVector.hpp"

namespace romea{

template< class PointType > using NormalSet = VectorOfEigenVector<PointType>;

}   // namespace romea

#endif  // ROMEA_CORE_COMMON_POINTSET_NORMALSET_HPP_
