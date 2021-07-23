#ifndef romea_Algorithm_hpp
#define romea_Algorithm_hpp

//std
#include <cmath>
#include <cassert>
#include <limits>
#include <algorithm>
#include <iostream>
#include <boost/optional.hpp>

namespace romea{

//--------------------------------------------------------------------------
template <typename RealType >
RealType sign(const RealType  &x)
{
  return (x < 0.) ? -1 : 1 ;
}

//--------------------------------------------------------------------------
template <typename RealType >
double signedMin(const RealType & x, const RealType & y)
{
  if(x >= 0 || y >= 0)
    return std::min(x,y);

  return std::max(x,y);
}

//--------------------------------------------------------------------------
template <typename RealType >
double signedFloor(const RealType & x)
{
  if(x>=0)
    return std::floor(x);
  else
    return std::ceil(x);
}

//--------------------------------------------------------------------------
template <typename RealType >
RealType near(const RealType & value1 ,
              const RealType & value2,
              double epsilon =std::numeric_limits<RealType>::epsilon())
{
  return std::abs(value1-value2) < 0.00001;
}

//replace by std::clamp with c++17
//--------------------------------------------------------------------------
template <typename RealType >
RealType clamp(const RealType & value ,
               const RealType & minValue,
               const RealType & maxValue)
{
  assert(minValue<=maxValue);
  return std::max(minValue,std::min(maxValue,value));
}

//--------------------------------------------------------------------------
template <typename RealType >
RealType symmetricClamp(const RealType & value ,
                        const RealType & absoluteMaxValue)
{
  return clamp(value,-absoluteMaxValue,absoluteMaxValue);
}

//--------------------------------------------------------------------------
template <typename RealType >
boost::optional<RealType> safeDivide(const RealType & numerator,
                                     const RealType & denominator)
{
  if(std::abs(denominator)<std::numeric_limits<RealType>::epsilon())
  {
    return boost::optional<RealType>();
  }
  else
  {
    return boost::optional<RealType>(numerator/denominator);
  }

}

//--------------------------------------------------------------------------
template<typename RealType>
static bool isApproximatelyEqual(RealType a,
                                 RealType b,
                                 RealType tolerance = std::numeric_limits<RealType>::epsilon())
{
  RealType diff = std::fabs(a - b);
  if (diff <= tolerance)
    return true;

  if (diff < std::fmax(std::fabs(a), std::fabs(b)) * tolerance)
    return true;

  return false;
}

//--------------------------------------------------------------------------
template<typename RealType>
static bool isApproximatelyZero(RealType a,
                                RealType tolerance = std::numeric_limits<RealType>::epsilon())
{
  if (std::fabs(a) <= tolerance)
    return true;
  return false;
}

////--------------------------------------------------------------------------
//template<typename RealType>
//static bool isDefinitelyLessThan(RealType a,
//                                 RealType b,
//                                 RealType tolerance = std::numeric_limits<RealType>::epsilon())
//{

////    return (b - a) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * tolerance);
//    RealType diff = a - b;
//    std::cout << "diff "<< diff<< std::endl;
//    if (diff < tolerance)
//        return true;

//    std::cout << " rol tol " << std::fmax(std::fabs(a), std::fabs(b)) * tolerance<<std::endl;
//    if (diff < std::fmax(std::fabs(a), std::fabs(b)) * tolerance)
//        return true;

//    return false;
//}

////--------------------------------------------------------------------------
//template<typename RealType>
//static bool isDefinitelyGreaterThan(RealType a,
//                                    RealType b,
//                                    RealType tolerance = std::numeric_limits<RealType>::epsilon())
//{
////  return (a - b) > ( (fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * tolerance);
//    RealType diff = a - b;
//    if (diff > tolerance)
//        return true;

//    if (diff > std::fmax(std::fabs(a), std::fabs(b)) * tolerance)
//        return true;

//    return false;
//}


}//romea

#endif
