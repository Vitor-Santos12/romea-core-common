#ifndef _romea_FirstOrderButterworth_hpp_
#define _romea_FirstOrderButterworth_hpp_

namespace romea{

class FirstOrderButterworth{

public:

  /**
   * Constructor
   * @param[in] weighting ; weight of the current computed value
   *                      = 1 : output will stay at the starting value
   *                      = 0 : output will be a mean between the 2 last value
   * @param[in] starting_value for the filter
   */
  FirstOrderButterworth(const double& weighting);


  double update(const double & measuredVatue);

  void reset();

private:

  double weighting_;
  double complementaryWeighting_;

  double filteredValue_;
  double previousMeasuredValue_;

  bool isInitialized_;
};

}
#endif
