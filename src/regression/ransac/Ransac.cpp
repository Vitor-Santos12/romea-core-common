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


// std
#include <limits>
#include <cassert>

// romea
#include "romea_core_common/regression/ransac/Ransac.hpp"
#include "romea_core_common/regression/ransac/RansacIterations.hpp"

namespace
{
const float FITTING_PROBABILITY_ = 0.99f;
const size_t MAXIMAL_NUMBER_OF_ITERATIONS = 1000;
}

namespace romea
{

//-----------------------------------------------------------------------------
Ransac::Ransac(
  RansacModel * ransacModel,
  double modelErrorDeviation)
: fittingProbability_(FITTING_PROBABILITY_),
  modelErrorDeviation_(modelErrorDeviation),
  maximalNumberOfIterations_(MAXIMAL_NUMBER_OF_ITERATIONS),
  ransacModel_(ransacModel)
{
  assert(modelErrorDeviation_ > std::numeric_limits<double>::epsilon());
}


//-----------------------------------------------------------------------------
bool Ransac::estimateModel()
{
  size_t iteration = 0;
  size_t bestNumberOfInliers = 0;
  size_t numberOfPoints = ransacModel_->getNumberOfPoints();
  size_t numberOfPointsToDrawModel = ransacModel_->getNumberOfPointsToDrawModel();

  if (numberOfPoints < ransacModel_->getMinimalNumberOfInliers()) {
    return false;
  }

  RansacIterations ransacIterations(numberOfPoints,
    fittingProbability_,
    MAXIMAL_NUMBER_OF_ITERATIONS);

  while (iteration < ransacIterations.get()) {
    // Draw and evaluate a new model
    if (ransacModel_->draw(modelErrorDeviation_)) {
      float numberOfInliers = ransacModel_->countInliers(modelErrorDeviation_);

      if (numberOfInliers > bestNumberOfInliers) {
        ransacIterations.update(numberOfInliers, numberOfPointsToDrawModel);
        bestNumberOfInliers = numberOfInliers;
      }
    }
    ++iteration;
  }

  // TODO(jean) improve
  if (bestNumberOfInliers <= numberOfPointsToDrawModel) {
    return false;
  }

  ransacModel_->refine();
  return true;
}

}  // namespace romea
