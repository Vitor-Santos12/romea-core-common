#ifndef romea_HomogeneousCoordinates_hpp
#define romea_HomogeneousCoordinates_hpp

//Eigen
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <Eigen/Core>
#pragma GCC diagnostic push


namespace romea {

template < typename Scalar>
class HomogeneousCoordinates2 : public Eigen::Matrix<Scalar,3,1>
{

public:


  inline HomogeneousCoordinates2(): Eigen::Matrix<Scalar,3,1>(0,0,1)
  {
  }

  inline HomogeneousCoordinates2(Scalar x, Scalar y): Eigen::Matrix<Scalar,3,1>(x,y,1)
  {
  }

  template<typename OtherDerived> inline
  HomogeneousCoordinates2(const Eigen::MatrixBase<OtherDerived>& other)
    : Eigen::Matrix<Scalar,3,1>(other)
  {
  }

  template<typename OtherDerived> inline
  HomogeneousCoordinates2 & operator=(const Eigen::MatrixBase <OtherDerived>& other)
  {
    this->Eigen::Matrix<Scalar,3,1>::operator=(other);
    return *this;
  }
};

//-----------------------------------------------------------------------------
template < typename Scalar>
class HomogeneousCoordinates3 : public Eigen::Matrix<Scalar,4,1>
{

public:

  inline HomogeneousCoordinates3(): Eigen::Matrix<Scalar,4,1>(0,0,0,1)
  {
  }

  inline HomogeneousCoordinates3(Scalar x, Scalar y, Scalar z): Eigen::Matrix<Scalar,4,1>(x,y,z,1)
  {
  }

  template<typename OtherDerived> inline
  HomogeneousCoordinates3(const Eigen::MatrixBase<OtherDerived>& other)
    : Eigen::Matrix<Scalar,4,1>(other)
  {
  }

  template<typename OtherDerived> inline
  HomogeneousCoordinates3 & operator=(const Eigen::MatrixBase <OtherDerived>& other)
  {
    this->Eigen::Matrix<Scalar,4,1>::operator=(other);
    return *this;
  }
};


using HomogeneousCoordinates2f=HomogeneousCoordinates2<float> ;
using HomogeneousCoordinates2d=HomogeneousCoordinates2<double> ;
using HomogeneousPoint2f=HomogeneousCoordinates2<float> ;
using HomogeneousPoint2d=HomogeneousCoordinates2<double> ;

using HomogeneousCoordinates3f=HomogeneousCoordinates3<float>;
using HomogeneousCoordinates3d=HomogeneousCoordinates3<double>;
using HomogeneousPoint3f=HomogeneousCoordinates3<float>;
using HomogeneousPoint3d=HomogeneousCoordinates3<double>;

}


#endif
