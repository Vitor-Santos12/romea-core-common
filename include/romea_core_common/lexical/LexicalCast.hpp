#ifndef _romea_LexicalCast_hpp_
#define _romea_LexicalCast_hpp_

#include <string>
#include <stdexcept>
#include <iostream>

namespace romea {

template<typename T>
T lexical_cast(const std::string & str, size_t & pos);

template<> inline double lexical_cast<double>(const std::string & str,size_t & pos)
{
  return std::stod(str,&pos);
}

template<> inline float lexical_cast<float>(const std::string & str, size_t &pos)
{
  return std::stof(str,&pos);
}

template<> inline int lexical_cast<int>(const std::string & str,size_t &pos)
{
  return std::stoi(str,&pos);
}

template<> inline long lexical_cast<long>(const std::string & str,size_t &pos)
{
  return std::stol(str,&pos);
}

template<> inline long double lexical_cast<long double>(const std::string & str,size_t &pos)
{
  return std::stold(str,&pos);
}

template<> inline long long lexical_cast<long long>(const std::string & str,size_t &pos)
{
  return std::stoll(str,&pos);
}

template<> inline unsigned long lexical_cast<unsigned long>(const std::string & str,size_t &pos)
{
  return std::stoul(str,&pos);
}

template<> inline unsigned long long lexical_cast<unsigned long long>(const std::string & str,size_t &pos)
{
  return std::stoull(str,&pos);
}

template<typename T>
T lexical_cast(const std::string & str)
{
  size_t pos;
  T value =lexical_cast<T>(str,pos);
  if(pos!=str.size())
  {
    throw(std::invalid_argument("lexical_cast"));
  }
  return value;
}

}//romea

#endif
