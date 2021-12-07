#ifndef _romea_DiagnosticCompare_hpp_
#define _romea_DiagnosticCompare_hpp_

//std
#include <limits>
#include <sstream>

//romea
#include "DiagnosticReport.hpp"

namespace romea {


template <typename T>
class  CheckCompareWith
{

public:

  CheckCompareWith(const std::string &name,
                   const T & value_to_compare_with_,
                   const T & epsilon);

  virtual ~ CheckCompareWith()=default;

public :

  virtual DiagnosticStatus evaluate(const T & value) =0;

  const DiagnosticReport & getReport() const;

protected:

//  const std::string & getValueName_() const;

  void setValue_(const T & value);

  void setDiagnostic_(const DiagnosticStatus & status,
                      const std::string & messageEnd);

  const DiagnosticStatus & getStatus_() const;

protected:

  T value_to_compare_with_;
  T epsilon_;

  DiagnosticReport report_;
};

//-----------------------------------------------------------------------------
template <typename T>
CheckCompareWith<T>::CheckCompareWith(const std::string & name,
                                      const T & value_to_compare_with,
                                      const T & epsilon):
  value_to_compare_with_(value_to_compare_with),
  epsilon_(epsilon),
  report_()
{
  report_.diagnostics.push_back(Diagnostic());
  report_.info[name]="";
}

//-----------------------------------------------------------------------------
template <typename T>
const DiagnosticReport & CheckCompareWith<T>::getReport() const
{
  return report_;
}

////-----------------------------------------------------------------------------
//template <typename T>
//const std::string & CheckCompareWith<T>::getValueName_() const
//{
//  return report_.info.begin()->first;
//}

//-----------------------------------------------------------------------------
template <typename T>
void CheckCompareWith<T>::setValue_(const T & value)
{
  report_.info.begin()->second= toStringInfoValue(value);
}

//-----------------------------------------------------------------------------
template <typename T>
void CheckCompareWith<T>::setDiagnostic_(const DiagnosticStatus & status,
                                         const std::string & messageEnd)
{
  Diagnostic & diagnostic= report_.diagnostics.front();
  diagnostic.message = report_.info.begin()->first + messageEnd;
  diagnostic.status=status;
}

//-----------------------------------------------------------------------------
template <typename T>
const DiagnosticStatus & CheckCompareWith<T>::getStatus_() const
{
  return this->report_.diagnostics.front().status;
}


}

#endif
