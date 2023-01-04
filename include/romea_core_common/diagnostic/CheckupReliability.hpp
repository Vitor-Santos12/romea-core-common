// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
// Add license

#ifndef ROMEA_CORE_COMMON__DIAGNOSTIC__CHECKUPRELIABILITY_HPP_
#define ROMEA_CORE_COMMON__DIAGNOSTIC__CHECKUPRELIABILITY_HPP_

// std
#include <string>
#include <mutex>

// romea
#include "romea_core_common/diagnostic/DiagnosticReport.hpp"

namespace romea
{

class CheckupReliability
{
public:
  CheckupReliability(
    const std::string & name,
    const double & low_reliability_threshold,
    const double & high_reliability_threshold);

  DiagnosticStatus evaluate(const double & reliability);

  DiagnosticReport getReport()const;

private:
  void setRelabilityValue_(const double & reliability);

  void setDiagnostic_(
    const DiagnosticStatus & status,
    const std::string & messageEnd);

private:
  double low_reliability_theshold_;
  double high_reliability_theshold_;

  mutable std::mutex mutex_;
  DiagnosticReport report_;
};

}  // namespace romea

#endif  // ROMEA_CORE_COMMON__DIAGNOSTIC__CHECKUPRELIABILITY_HPP_
