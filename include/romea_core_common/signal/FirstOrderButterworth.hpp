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


#ifndef ROMEA_CORE_COMMON__SIGNAL__FIRSTORDERBUTTERWORTH_HPP_
#define ROMEA_CORE_COMMON__SIGNAL__FIRSTORDERBUTTERWORTH_HPP_

namespace romea
{
namespace core
{

class FirstOrderButterworth
{
public:
  /**
   * Constructor
   * @param[in] weighting ; weight of the current computed value
   *                      = 1 : output will stay at the starting value
   *                      = 0 : output will be a mean between the 2 last value
   * @param[in] starting_value for the filter
   */
  explicit FirstOrderButterworth(const double & weighting);


  double update(const double & measuredVatue);

  void reset();

private:
  double weighting_;
  double complementaryWeighting_;

  double filteredValue_;
  double previousMeasuredValue_;

  bool isInitialized_;
};

}  // namespace core
}  // namespace romea

#endif  // ROMEA_CORE_COMMON__SIGNAL__FIRSTORDERBUTTERWORTH_HPP_
