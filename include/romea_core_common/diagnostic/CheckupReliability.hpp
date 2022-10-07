#ifndef _romea_CheckupReliability_hpp_
#define _romea_CheckupReliability_hpp_

#include "DiagnosticReport.hpp"
#include <mutex>

namespace romea {

class  CheckupReliability
{

public:

  CheckupReliability(const std::string &name,
                     const double & low_reliability_threshold,
                     const double & high_reliability_threshold);

  DiagnosticStatus evaluate(const double & reliability);

  DiagnosticReport getReport()const;

private :

  void setRelabilityValue_(const double & reliability);

  void setDiagnostic_(const DiagnosticStatus & status,
                      const std::string & messageEnd);

private:

  double low_reliability_theshold_;
  double high_reliability_theshold_;

  mutable std::mutex mutex_;
  DiagnosticReport report_;
};


}// namespace


#endif
