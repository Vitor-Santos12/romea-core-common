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


#ifndef ROMEA_CORE_COMMON__TRANSFORM__SMARTROTATION3D_HPP_
#define ROMEA_CORE_COMMON__TRANSFORM__SMARTROTATION3D_HPP_

#include <Eigen/Core>

namespace romea
{

class SmartRotation3D
{
public:
  SmartRotation3D();

  SmartRotation3D(
    const double & angleAroundXAxis,
    const double & angleAroundYAxis,
    const double & angleAroundZAxis);

  explicit SmartRotation3D(const Eigen::Vector3d & angles);

  void init(
    const double & angleAroundXAxis,
    const double & angleAroundYAxis,
    const double & angleAroundZAxis);

  void init(const Eigen::Vector3d & angles);


  Eigen::Vector3d operator*(const Eigen::Vector3d & T)const;

  Eigen::Matrix3d dRTdAngles(const Eigen::Vector3d & T) const;

  const Eigen::Matrix3d & dRdAngleAroundXAxis()const;

  const Eigen::Matrix3d & dRdAngleAroundYAxis()const;

  const Eigen::Matrix3d & dRdAngleAroundZAxis()const;

  const Eigen::Matrix3d & R() const;

private:
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

#endif  // ROMEA_CORE_COMMON__TRANSFORM__SMARTROTATION3D_HPP_
