#ifndef ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACRANDOMCORRESPONDENCES_HPP_
#define ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACRANDOMCORRESPONDENCES_HPP_

// stl
#include <vector>
#include <random>

// romea
#include "romea_core_common/pointset/PointSet.hpp"
#include "romea_core_common/pointset/PointTraits.hpp"
#include "romea_core_common/pointset/algorithms/Correspondence.hpp"

// Eigen
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

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_REGRESSION_RANSAC_RANSACRANDOMCORRESPONDENCES_HPP_
