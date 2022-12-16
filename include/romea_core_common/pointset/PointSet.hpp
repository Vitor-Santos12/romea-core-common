#ifndef ROMEA_CORE_COMMON_POINTSET_POINTSET_HPP_ 
#define ROMEA_CORE_COMMON_POINTSET_POINTSET_HPP_ 

// romea
#include "romea_core_common/coordinates/CartesianCoordinates.hpp"
#include "romea_core_common/coordinates/HomogeneousCoordinates.hpp"
#include "romea_core_common/containers/Eigen/VectorOfEigenVector.hpp"

namespace romea{

template< class PointType > using PointSet = VectorOfEigenVector<PointType>;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_POINTSET_POINTSET_HPP_
