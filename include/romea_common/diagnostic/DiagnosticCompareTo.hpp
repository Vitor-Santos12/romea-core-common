#ifndef _romea_DiagnosticCompare_hpp_
#define _romea_DiagnosticCompare_hpp_

//std
#include <limits>
#include <sstream>

//romea
#include "DiagnosticReport.hpp"

namespace romea {


template <typename T>
class  DiagnosticCompareTo
{

public:

  DiagnosticCompareTo(const std::string &name,
                      const T & value_to_compare_with_,
                      const T & epsilon);

  virtual ~ DiagnosticCompareTo()=default;

public :

  virtual DiagnosticStatus evaluate(const T & value) =0;

  const DiagnosticReport & getReport() const;

protected:

  const std::string & getValueName_() const;

  void setValue_(const T & value);

protected:

  T value_to_compare_with_;
  T epsilon_;

  DiagnosticReport report_;
};

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticCompareTo<T>::DiagnosticCompareTo(const std::string & name,
                                            const T & value_to_compare_with,
                                            const T & epsilon):
  value_to_compare_with_(value_to_compare_with),
  epsilon_(epsilon),
  report_()
{
  report_.info[name]="";
}

//-----------------------------------------------------------------------------
template <typename T>
const DiagnosticReport & DiagnosticCompareTo<T>::getReport() const
{
  return report_;
}

//-----------------------------------------------------------------------------
template <typename T>
const std::string & DiagnosticCompareTo<T>::getValueName_() const
{
  return report_.info.begin()->first;
}

//-----------------------------------------------------------------------------
template <typename T>
void DiagnosticCompareTo<T>::setValue_(const T & value)
{
  report_.info.begin()->second= toStringInfoValue(value);
}


}

#endif
