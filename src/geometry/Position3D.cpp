// romea
#include "romea_core_common/geometry/Position3D.hpp"

namespace romea {

//--------------------------------------------------------------------------
Position3D::Position3D():
  position(Eigen::Vector3d::Zero()),
  covariance(Eigen::Matrix3d::Zero())
{
}

}   // namespace romea

