#ifndef romea_RansacRandomCorrespondences_hpp
#define romea_RansacRandomCorrespondences_hpp

//romea
#include "../../pointset/PointSet.hpp"
#include "../../pointset/PointTraits.hpp"
#include "../../pointset/algorithms/Correspondence.hpp"

//stl
#include <vector>
#include <random>

//Eigen
#include <Eigen/Eigen>
#include <unsupported/Eigen/MatrixFunctions>

namespace romea {

template <class PointType>
class RansacRandomCorrespondences{

public :

  RansacRandomCorrespondences();

  void computeScale(const PointType & pointSetMin,
                    const PointType & pointSetMax);

  std::vector<Correspondence>
  drawPoints(const PointSet<PointType> & sourcePointSet,
             const std::vector<Correspondence> & correspondences,
             const size_t & numberOfRandomCorrespondences);

private :

  void resetWeights_();

  void computeCumSumWeights_();

  void updateWeights_(const PointSet<PointType> & preconditionedSourcePointSet,
                      const std::vector<Correspondence> & correspondences,
                      const size_t & correspondenceIndex);


private :

  size_t numberOfCorrespondences_;

  PointType scale_;
  std::vector<double> weights_;
  std::vector<double> cumSumWeights_;


  std::default_random_engine randomGenerator_;
  std::uniform_real_distribution<double> uniformDistribution_;

public :

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW_IF_VECTORIZABLE_FIXED_SIZE(
      typename PointType::Scalar, PointTraits<PointType>::SIZE)

};

}
#endif
