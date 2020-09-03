#ifndef _romea_SharedVariable_hpp_
#define _romea_SharedVariable_hpp_

#include <mutex>

namespace romea {

template <typename T>
class SharedVariable
{
public:
  SharedVariable();
  SharedVariable(const T & value);
  SharedVariable & operator=(const T & value);
  SharedVariable(const SharedVariable &)=delete;
  SharedVariable & operator=(const SharedVariable &)=delete;

public :

  operator T() const;
  void store(const T & value);
  T load() const;

private:

  T value_;
  mutable std::mutex mutex_;
};

//-----------------------------------------------------------------------------
template <typename T>
SharedVariable<T>::SharedVariable() :
  value_(T()), mutex_()
{
}

//-----------------------------------------------------------------------------
template <typename T>
SharedVariable<T>::SharedVariable(const T & value) :
  value_(value), mutex_()
{

}

//-----------------------------------------------------------------------------
template <typename T>
SharedVariable<T> & SharedVariable<T>::operator=(const T & value)
{
  store(value);
  return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
SharedVariable<T>::operator T() const
{
  return load();
}

//-----------------------------------------------------------------------------
template <typename T>
void SharedVariable<T>::store(const T & value)
{
  std::lock_guard<std::mutex> lock(mutex_);
  value_ = value;
}

//-----------------------------------------------------------------------------
template <typename T>
T SharedVariable<T>::load() const
{
  std::lock_guard<std::mutex> lock(mutex_);
  return value_;
}

}

#endif
