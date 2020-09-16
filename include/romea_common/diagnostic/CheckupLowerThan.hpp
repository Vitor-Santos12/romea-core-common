#ifndef _romea_DiagnosticLowerThan2_hpp_
#define _romea_DiagnosticLowerThan2_hpp_


#include "CheckupCompareWith.hpp"

namespace romea {



template <typename T>
class  DiagnosticLowerThan2 final : public CheckCompareWith<T>
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
  CheckCompareWith<T>(name,maximal_value,epsilon)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus DiagnosticLowerThan2<T>::evaluate(const T & value)
{
  if(value < this->value_to_compare_with_+this->epsilon_)
  {
    this->setDiagnostic_(DiagnosticStatus::OK," is OK.");
  }
  else
  {
    this->setDiagnostic_(DiagnosticStatus::ERROR," is too high.");
  }

  this->setValue_(value);
  return this->getStatus_();;
}


}// namespace


#endif



