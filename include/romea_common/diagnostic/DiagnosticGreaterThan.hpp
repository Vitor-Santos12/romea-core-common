#ifndef _romea_DiagnosticGreaterThan2_hpp_
#define _romea_DiagnosticGreaterThan2_hpp_


#include "DiagnosticCompareTo.hpp"

namespace romea {



template <typename T>
class  DiagnosticGreaterThan2 final : public DiagnosticCompareTo<T>
{
public:


  DiagnosticGreaterThan2(const std::string &name,
                         const T &minimal_value,
                         const T &epsilon= std::numeric_limits<T>::epsilon());


  DiagnosticStatus evaluate(const T & value) override;

};

//-----------------------------------------------------------------------------
template< typename T>
DiagnosticGreaterThan2<T>::DiagnosticGreaterThan2(const std::string &name,
                                                  const T &minimal_value,
                                                  const T &epsilon):
  DiagnosticCompareTo<T>(name,minimal_value,epsilon)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus DiagnosticGreaterThan2<T>::evaluate(const T & value)
{
  if(value > this->value_to_compare_with_-this->epsilon_)
  {
    this->report_.status=DiagnosticStatus::OK;
    this->report_.message=this->getValueName_()+ " is OK.";
  }
  else
  {
    this->report_.status=DiagnosticStatus::ERROR;
    this->report_.message=this->getValueName_()+ " is too low.";
  }
  this->setValue_(value);
  return this->report_.status;
}

}

#endif



