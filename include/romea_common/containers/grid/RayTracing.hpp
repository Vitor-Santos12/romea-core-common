#ifndef romea_RayCasting_hpp
#define romea_RayCasting_hpp

//romea
#include "GridIndexMapping.hpp"
#include "../Eigen/VectorOfEigenVector.hpp"

namespace romea {


template <typename Scalar , size_t DIM>
class RayCasting
{

public :

  using PointType =Eigen::Matrix<Scalar,DIM,1>;
  using CellIndexes =Eigen::Matrix<size_t,DIM,1>;

public :

  RayCasting();

  RayCasting(GridIndexMapping<Scalar,DIM> * gridIndexMapping);

public :

  void setGridIndexMapping(GridIndexMapping<Scalar,DIM> * gridIndexMapping);

  void setOriginPoint(const PointType & originPoint);

  const PointType & getOriginPoint()const;

  const CellIndexes & getOriginPointIndexes() const;

  void setEndPoint(const PointType & endPoint);

  const PointType & getEndPoint()const;

  const CellIndexes & getEndPointIndexes() const;

  size_t computeRayNumberOfCells()const;

public :

  VectorOfEigenVector<CellIndexes> cast();

  VectorOfEigenVector<CellIndexes> cast(const PointType & endPoint);

  VectorOfEigenVector<CellIndexes> cast(const PointType & originPoint,const PointType & endPoint);

  void next(CellIndexes & cellIndexes);

private :

  GridIndexMapping<Scalar,DIM> * gridIndexMapping_;

  PointType rayOriginPoint_;
  PointType rayEndPoint_;

  CellIndexes rayOriginIndexes_;
  CellIndexes rayEndIndexes_;

  PointType rayTMax_;
  PointType rayTDelta_;
  PointType rayDirection_;
  Eigen::Matrix<int,DIM,1> rayStep_;

public :
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF_VECTORIZABLE_FIXED_SIZE(Scalar,DIM)

};

using RayCasting2f=RayCasting<float,2>;
using RayCasting3f=RayCasting<float,3>;
using RayCasting2d=RayCasting<double,2>;
using RayCasting3d=RayCasting<double,3> ;


}

#endif
