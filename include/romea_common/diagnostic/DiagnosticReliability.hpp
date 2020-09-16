#ifndef _romea_ReliabilityDiagnostic2_hpp_
#define _romea_ReliabilityDiagnostic2_hpp_

#include "DiagnosticReport.hpp"

namespace romea {

class  DiagnosticReliability2
{

public:

  DiagnosticReliability2(const std::string &name,
                         const double & low_reliability_threshold,
                         const double & high_reliability_threshold);

  DiagnosticStatus evaluate(const double & reliability);

  const DiagnosticReport & getReport()const;

private:

  double low_reliability_theshold_;
  double high_reliability_theshold_;

  DiagnosticReport report_;
};


}// namespace


#endif
