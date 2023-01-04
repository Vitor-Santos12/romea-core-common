// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

// std
#include <sstream>
#include <iostream>
#include <string>

// romea
#include "romea_core_common/diagnostic/CheckupRate.hpp"


namespace romea
{

//-----------------------------------------------------------------------------
template<typename CheckupType>
CheckupRate<CheckupType>::CheckupRate(
  const std::string & name,
  const double & rate,
  const double & espilon)
: rateMonitoring_(rate),
  checkup_(name + "_rate",
    rate,
    espilon,
    Diagnostic(DiagnosticStatus::ERROR, "no data received from " + name))
{
}


//-----------------------------------------------------------------------------
template<typename CheckupType>
DiagnosticStatus CheckupRate<CheckupType>::evaluate(const Duration & stamp)
{
  double rate = rateMonitoring_.update(stamp);
  return checkup_.evaluate(rate);
}

//-----------------------------------------------------------------------------
template<typename CheckupType>
DiagnosticReport CheckupRate<CheckupType>::getReport() const
{
  return checkup_.getReport();
}

//-----------------------------------------------------------------------------
template<typename CheckupType>
bool CheckupRate<CheckupType>::heartBeatCallback(const Duration & stamp)
{
  if (rateMonitoring_.timeout(stamp)) {
    checkup_.timeout();
    return false;
  }
  return true;
}

template class CheckupRate<CheckupGreaterThan<double>>;
template class CheckupRate<CheckupEqualTo<double>>;

}  // namespace romea
