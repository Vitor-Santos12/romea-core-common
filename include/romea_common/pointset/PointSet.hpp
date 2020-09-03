#ifndef romea_PointSet_hpp
#define romea_PointSet_hpp

//romea
#include "../coordinates/CartesianCoordinates.hpp"
#include "../coordinates/HomogeneousCoordinates.hpp"
#include "../containers/Eigen/VectorOfEigenVector.hpp"

namespace romea{

template< class PointType > using PointSet = VectorOfEigenVector<PointType>;

}
#endif
