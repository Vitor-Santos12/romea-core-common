#ifndef ROMEA_CORE_COMMON_TRANSFORM_SMARTROTATION3D_HPP_
#define ROMEA_CORE_COMMON_TRANSFORM_SMARTROTATION3D_HPP_

// romea
#include <Eigen/Core>

namespace romea {

class SmartRotation3D
{
public :

  SmartRotation3D();

  SmartRotation3D(const double & angleAroundXAxis,
                  const double & angleAroundYAxis,
                  const double & angleAroundZAxis);

  explicit SmartRotation3D(const Eigen::Vector3d & angles);

  void init(const double & angleAroundXAxis,
            const double & angleAroundYAxis,
            const double & angleAroundZAxis);

  void init(const Eigen::Vector3d & angles);


  Eigen::Vector3d operator*(const Eigen::Vector3d & T)const;

  Eigen::Matrix3d dRTdAngles(const Eigen::Vector3d & T) const;

  const Eigen::Matrix3d & dRdAngleAroundXAxis()const;

  const Eigen::Matrix3d & dRdAngleAroundYAxis()const;

  const Eigen::Matrix3d & dRdAngleAroundZAxis()const;

  const Eigen::Matrix3d & R() const;


private :

  Eigen::Matrix3d Rx_;
  Eigen::Matrix3d Ry_;
  Eigen::Matrix3d Rz_;
  Eigen::Matrix3d R_;
  Eigen::Matrix3d dRxdAngleX_;
  Eigen::Matrix3d dRydAngleY_;
  Eigen::Matrix3d dRzdAngleZ_;
  Eigen::Matrix3d dRdAngleX_;
  Eigen::Matrix3d dRdAngleY_;
  Eigen::Matrix3d dRdAngleZ_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_TRANSFORM_SMARTROTATION3D_HPP_
