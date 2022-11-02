#ifndef _romea_CheckupLowerThan_hpp_
#define _romea_CheckupLowerThan_hpp_


#include "Checkup.hpp"

namespace romea {



template <typename T>
class  CheckupLowerThan : public Checkup<T>
{

public:


  CheckupLowerThan(const std::string &name,
                   const T &maximal_value,
                   const T &epsilon,
                   const Diagnostic & diagnostic=Diagnostic());

  DiagnosticStatus evaluate(const T & value) override;

};



//-----------------------------------------------------------------------------
template< typename T>
CheckupLowerThan<T>::CheckupLowerThan(const std::string & name,
                                      const T & maximal_value,
                                      const T & epsilon,
                                      const Diagnostic & diagnostic):
  Checkup<T>(name,maximal_value,epsilon,diagnostic)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckupLowerThan<T>::evaluate(const T & value)
{
  std::lock_guard<std::mutex> lock(this->mutex_);
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



