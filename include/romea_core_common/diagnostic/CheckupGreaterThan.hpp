#ifndef _romea_CheckupGreaterThan_hpp_
#define _romea_CheckupGreaterThan_hpp_


#include "Checkup.hpp"

namespace romea {



template <typename T>
class  CheckupGreaterThan : public Checkup<T>
{
public:


  CheckupGreaterThan(const std::string &name,
                     const T &minimal_value,
                     const T &epsilon,
                     const Diagnostic & diagnostic=Diagnostic());


  DiagnosticStatus evaluate(const T & value) override;

};

//-----------------------------------------------------------------------------
template< typename T>
CheckupGreaterThan<T>::CheckupGreaterThan(const std::string &name,
                                          const T &minimal_value,
                                          const T &epsilon,
                                          const Diagnostic & diagnostic):
  Checkup<T>(name,minimal_value,epsilon,diagnostic)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckupGreaterThan<T>::evaluate(const T & value)
{
  std::lock_guard<std::mutex> lock(this->mutex_);
  if(value > this->value_to_compare_with_-this->epsilon_)
  {
    this->setDiagnostic_(DiagnosticStatus::OK," is OK.");
  }
  else
  {
    this->setDiagnostic_(DiagnosticStatus::ERROR," is too low.");
  }
  this->setValue_(value);
  return this->getStatus_();;
}

}

#endif



