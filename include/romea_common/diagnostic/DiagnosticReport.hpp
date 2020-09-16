#ifndef _romea_DiagnosticReport_hpp_
#define _romea_DiagnosticReport_hpp_

//boost
#include <boost/optional.hpp>

//std
#include <sstream>
#include <map>

//romea
#include "DiagnosticStatus.hpp"

namespace romea
{

struct DiagnosticReport
{
  DiagnosticReport();

  DiagnosticStatus status;
  std::string message;
  std::map<std::string,std::string> info;

};

std::ostream & operator <<(std::ostream & os, const DiagnosticReport & report);
DiagnosticReport & operator+=(DiagnosticReport & report1, const DiagnosticReport & report2);

//-----------------------------------------------------------------------------
template <typename T>
std::string toStringInfoValue(const T & infoValue)
{
  std::ostringstream os;
  os << infoValue;
  return os.str();
}

//-----------------------------------------------------------------------------
template <typename T>
void setReportInfo(DiagnosticReport & report,
                   const std::string & infoName,
                   const T & infoValue)
{
  report.info[infoName]=toStringInfoValue(infoValue);
}

//-----------------------------------------------------------------------------
template <typename T>
void setReportInfo(DiagnosticReport & report,
                   const std::string & infoName,
                   const boost::optional<T> & infoValue)
{
  if(infoValue.is_initialized())
  {
    setReportInfo(report,infoName,*infoValue);
  }
  else
  {
    report.info[infoName]="";
  }
}


}

#endif
