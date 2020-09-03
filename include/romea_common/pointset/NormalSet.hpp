#ifndef romea_NormalSet_hpp
#define romea_NormalSet_hpp

#include "../containers/Eigen/VectorOfEigenVector.hpp"

namespace romea{

template< class PointType > using NormalSet = VectorOfEigenVector<PointType>;

}
#endif
