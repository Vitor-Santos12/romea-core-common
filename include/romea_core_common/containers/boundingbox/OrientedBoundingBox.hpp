#ifndef ROMEA_CORE_COMMON_CONTAINERS_BOUNDINGBOX_ORIENTEDBOUNDINGBOX_HPP_
#define ROMEA_CORE_COMMON_CONTAINERS_BOUNDINGBOX_ORIENTEDBOUNDINGBOX_HPP_

#include "romea_core_common/containers/boundingbox/AxisAlignedBoundingBox.hpp"

namespace romea {

template <typename Scalar, size_t DIM>
class OrientedBoundingBox
{
public :
  using AABBType = AxisAlignedBoundingBox<Scalar, DIM>;
  using PointType = Eigen::Matrix<Scalar, DIM, 1>;
  using RotationType = Eigen::Matrix<Scalar, DIM, DIM> ;

public :
  OrientedBoundingBox();

  OrientedBoundingBox(const PointType & centerPosition,
                      const PointType & halfWidthExtents,
                      const RotationType & rotation);

  virtual ~OrientedBoundingBox() = default;

public :
  const PointType & getCenterPosition()const;

  const PointType & getHalfWidthExtents()const;

  const RotationType & getRotationMatrix()const;

  virtual AABBType toAxisAlignedBoundingBox()const;

  virtual bool isInside(const PointType & point) const;

protected :
  AABBType aabb_;
  RotationType rotation_;
};

typedef OrientedBoundingBox<float, 2> OrientedBoundingBox2f;
typedef OrientedBoundingBox<float, 3> OrientedBoundingBox3f;
typedef OrientedBoundingBox<double, 2> OrientedBoundingBox2d;
typedef OrientedBoundingBox<double, 3> OrientedBoundingBox3d;

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONTAINERS_BOUNDINGBOX_ORIENTEDBOUNDINGBOX_HPP_
