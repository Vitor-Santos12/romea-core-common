#ifndef _romea_CheckupGreaterThan_hpp_
#define _romea_CheckupGreaterThan_hpp_


#include "CheckupCompareWith.hpp"

namespace romea {



template <typename T>
class  CheckupGreaterThan final : public CheckCompareWith<T>
{
public:


  CheckupGreaterThan(const std::string &name,
                     const T &minimal_value,
                     const T &epsilon= std::numeric_limits<T>::epsilon());


  DiagnosticStatus evaluate(const T & value) override;

};

//-----------------------------------------------------------------------------
template< typename T>
CheckupGreaterThan<T>::CheckupGreaterThan(const std::string &name,
                                          const T &minimal_value,
                                          const T &epsilon):
  CheckCompareWith<T>(name,minimal_value,epsilon)
{

}

//-----------------------------------------------------------------------------
template <typename T>
DiagnosticStatus CheckupGreaterThan<T>::evaluate(const T & value)
{
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



