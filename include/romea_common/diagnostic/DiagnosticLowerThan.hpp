#ifndef _romea_DiagnosticLowerThan2_hpp_
#define _romea_DiagnosticLowerThan2_hpp_


#include "DiagnosticCompareTo.hpp"

namespace romea {



template <typename T>
class  DiagnosticLowerThan2 final : public DiagnosticCompareTo<T>
{

public:


  DiagnosticLowerThan2(const std::string &name,
                       const T &maximal_value,
                       const T &epsilon);

  DiagnosticStatus evaluate(const T & value) override;

};



//-----------------------------------------------------------------------------
template< typename T>
DiagnosticLowerThan2<T>::DiagnosticLowerThan2(const std::string & name,
                                              const T & maximal_value,
                                              const T & epsilon):
  DiagnosticCompareTo<T>(name,maximal_value,epsilon)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus DiagnosticLowerThan2<T>::evaluate(const T & value)
{
  if(value < this->value_to_compare_with_+this->epsilon_)
  {
    this->report_.status = DiagnosticStatus::OK;
    this->report_.message = this->getValueName_()+ " is OK.";
  }
  else
  {
    this->report_.status = DiagnosticStatus::ERROR;
    this->report_.message = this->getValueName_()+ " is too high.";
  }
  this->setValue_(value);
  return this->report_.status;
}


}// namespace


#endif



