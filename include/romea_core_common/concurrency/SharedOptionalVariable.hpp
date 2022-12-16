#ifndef ROMEA_CORE_COMMON_CONCURRENCY_SHAREDOPTIONALVARIABLE_HPP_
#define ROMEA_CORE_COMMON_CONCURRENCY_SHAREDOPTIONALVARIABLE_HPP_

#include <mutex>
#include <optional>

namespace romea {

template <typename T>
class SharedOptionalVariable
{
public:
  SharedOptionalVariable();
  explicit SharedOptionalVariable(const T & value);

  SharedOptionalVariable & operator=(const T & value) = delete;
  SharedOptionalVariable(const SharedOptionalVariable &) = delete;
  SharedOptionalVariable & operator=(const SharedOptionalVariable &) = delete;

public :

  void store(const T & value);
  std::optional<T> consume();

private:
  std::optional<T> value_;
  mutable std::mutex mutex_;
};

//-----------------------------------------------------------------------------
template <typename T>
SharedOptionalVariable<T>::SharedOptionalVariable() :
  value_(),
  mutex_()
{
}

//-----------------------------------------------------------------------------
template <typename T>
SharedOptionalVariable<T>::SharedOptionalVariable(const T & value) :
  value_(value),
  mutex_()
{
}

////-----------------------------------------------------------------------------
//template <typename T>
//ProducerConsumerVariable<T> & ProducerConsumerVariable<T>::operator=(const T & value)
//{
//  store(value);
//  return *this;
//}

//-----------------------------------------------------------------------------
template <typename T>
void SharedOptionalVariable<T>::store(const T & value)
{
  std::lock_guard<std::mutex> lock(mutex_);
  value_ = value;
}

//-----------------------------------------------------------------------------
template <typename T>
std::optional<T> SharedOptionalVariable<T>::consume()
{
  std::lock_guard<std::mutex> lock(mutex_);
  auto value = value_;
  value_.reset();
  return value;
}

}  // namespace romea

#endif  // ROMEA_CORE_COMMON_CONCURRENCY_SHAREDOPTIONALVARIABLE_HPP_
