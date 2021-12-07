#ifndef romea_LeastSquares_hpp
#define romea_LeastSquares_hpp

//Eigen
#include <Eigen/Eigen>

namespace romea{

template <typename RealType>
class LeastSquares {

public:

  using Matrix = Eigen::Matrix<RealType,Eigen::Dynamic,Eigen::Dynamic>;
  using Vector = Eigen::Matrix<RealType,Eigen::Dynamic,1> ;

  LeastSquares();

  LeastSquares(const size_t &estimateSize);

  LeastSquares(const size_t &estimateSize, const size_t & dataSize);

  virtual ~LeastSquares()=default;

  void setEstimateSize(const size_t & dataSize);

  bool setDataSize(const size_t & dataSize);

public :

  Vector estimateUsingCholeskyDecomposition();

  Vector estimateUsingSVD();

  Vector weightedEstimate();

  Matrix computeEstimateCovariance(const RealType & dataVariance);

  void setPreconditionner(const Matrix & Ac , const Vector &Bc);

  void setPreconditionner(const Matrix & Ac);

public :

  Matrix & getJ();
  const Matrix & getJ()const ;

  Vector & getY();
  const Vector & getY()const ;

  Vector & getW();
  const Vector & getW()const ;

private :


  void weightJAndY_();
  void computeJTJ_();
  void computeJTY_();

private :

  int dataSize_;
  int estimateSize_;

  Matrix Ac_;
  Vector Bc_;

  Matrix J_;
  Vector Y_;
  Vector W_;

  Matrix JtJ_;
  Matrix inverseJtJ_;
  Vector JtY_;
};

}//romea

#endif
