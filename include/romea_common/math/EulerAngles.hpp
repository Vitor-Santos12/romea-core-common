#ifndef romea_EulerAngles_hpp
#define romea_EulerAngles_hpp

//Eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

//std
#include <cmath>

namespace {

static constexpr auto M_2PI    = 2 * M_PI;
static constexpr auto M_4PI    = 4 * M_PI;
}

namespace romea {


//-----------------------------------------------------------------------------
template < typename Scalar>
Scalar between0And2Pi(Scalar val)
{
  assert(val> - M_4PI && val < M_4PI);

  double value = std::fmod(val, M_2PI);
  return value < 0 ? value + M_2PI : value;
}

//-----------------------------------------------------------------------------
template < typename Scalar>
Scalar betweenMinusPiAndPi(Scalar val)
{
  assert(val> - M_4PI && val < M_4PI);

  double value = std::fmod(val, M_2PI);

  if (value < -M_PI)
    value += M_2PI;
  else if (value > M_PI)
    value -= M_2PI;

  return value;
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Scalar rotation2DToEulerAngle(const Eigen::Matrix<Scalar,2,2> & rotation)
{
  return between0And2Pi(std::atan2(rotation(1,0)-rotation(0,1),rotation(0,0) + rotation(1,1)));
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Eigen::Matrix<Scalar,2,2> eulerAngleToRotation2D(const Scalar & eulerAngle)
{
  return (Eigen::Matrix<Scalar,2,2>()<<std::cos(eulerAngle), -std::sin(eulerAngle),
          std::sin(eulerAngle),std::cos(eulerAngle)).finished();
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Eigen::Matrix<Scalar,3,1> rotation3DToEulerAngles(const Eigen::Matrix<Scalar,3,3> & inRotation)
{
  Eigen::Matrix<Scalar,3,1> eulerAngles;
  eulerAngles[0] = between0And2Pi(std::atan2(inRotation(2,1),inRotation(2,2)));
  eulerAngles[1] = between0And2Pi(-std::asin(inRotation(2,0)));
  eulerAngles[2] = between0And2Pi( std::atan2(inRotation(1,0),inRotation(0,0)));

  return eulerAngles;
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Eigen::Matrix<Scalar,3,1> quaternionToEulerAngles(const Eigen::Quaternion<Scalar> & quaternion)
{
  return rotation3DToEulerAngles(quaternion.normalized().toRotationMatrix());
}

//-----------------------------------------------------------------------------
template <typename Scalar>
Eigen::Matrix<Scalar,3,3> eulerAnglesToRotation3D(const Eigen::Matrix<Scalar,3,1> & inEulerAngles)
{
  return  Eigen::Matrix<Scalar,3,3>( Eigen::AngleAxis<Scalar>(inEulerAngles(2), Eigen::Matrix<Scalar,3,1> ::UnitZ()) *
                                     Eigen::AngleAxis<Scalar>(inEulerAngles(1), Eigen::Matrix<Scalar,3,1> ::UnitY()) *
                                     Eigen::AngleAxis<Scalar>(inEulerAngles(0), Eigen::Matrix<Scalar,3,1> ::UnitX()));
}

}//romea

#endif
