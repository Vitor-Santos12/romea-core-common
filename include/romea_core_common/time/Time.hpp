// Copyright 2022 INRAE, French National Research Institute for Agriculture, Food and Environment
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.


#ifndef ROMEA_CORE_COMMON__TIME__TIME_HPP_
#define ROMEA_CORE_COMMON__TIME__TIME_HPP_

// std
#include <chrono>
#include <ctime>
#include <string>
#include <cassert>
#include <iomanip>
#include <sstream>

namespace romea
{

using Duration = std::chrono::duration<long long int, std::nano>;

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

//-----------------------------------------------------------------------------
inline TimePoint now()
{
  return std::chrono::high_resolution_clock::now();
}

//-----------------------------------------------------------------------------
inline Duration duration(const TimePoint endDate, const TimePoint startDate)
{
  return std::chrono::duration_cast<Duration>(endDate - startDate);
}


//-----------------------------------------------------------------------------
inline Duration durationFromNanoSecond(const long long int & nanoseconds)
{
  return Duration(nanoseconds);
}

//-----------------------------------------------------------------------------
inline Duration durationFromMicroSecond(const long long int & microseconds)
{
  return Duration(microseconds * 1000);
}

//-----------------------------------------------------------------------------
inline Duration durationFromMilliSecond(const long long int & milliseconds)
{
  return Duration(milliseconds * 1000000);
}

//-----------------------------------------------------------------------------
inline Duration durationFromSecond(const double & seconds)
{
  return Duration(static_cast<long long int>(seconds * 1000000000));
}

//-----------------------------------------------------------------------------
inline long long int durationToNanoSecond(const Duration & duration)
{
  return duration.count();
}

//-----------------------------------------------------------------------------
inline long long int durationToMicroSecond(const Duration & duration)
{
  return duration.count() / 1000;
}

//-----------------------------------------------------------------------------
inline long long int durationToMilliSecond(const Duration & duration)
{
  return duration.count() / 1000000;
}

//-----------------------------------------------------------------------------
inline double durationToSecond(const Duration & duration)
{
  return duration.count() / 1000000000.;
}


//-----------------------------------------------------------------------------
inline Duration makeDuration(
  const int & hour,
  const int & min,
  const double & sec)
{
  return durationFromSecond((hour * 3600 + min * 60 + sec));
}

//-----------------------------------------------------------------------------
inline std::string asString(const Duration & duration)
{
  double t = durationToSecond(duration);

  int hours = static_cast<int>(t / 3600);
  t -= hours * 3600;
  int mins = static_cast<int>(t / 60);
  t -= mins * 60;
  int secs = static_cast<int>(t);
  t -= secs;

  std::stringstream ss;
  ss << std::setfill('0');
  ss << std::setw(2) << hours;
  ss << ":" << std::setw(2) << mins;
  ss << ":" << std::setw(2) << secs;
  ss << "." << int(t * 100);
  return ss.str();
}

//-----------------------------------------------------------------------------
inline TimePoint makeTimePoint(
  const int & year,
  const int & mon,
  const int & day,
  const int & hour,
  const int & min,
  const double & sec)
{
  std::tm tm;
  tm.tm_sec = static_cast<int>(sec);        // second of minute (0 .. 59 and 60 for leap seconds)
  tm.tm_min = min;        // minute of hour (0 .. 59)
  tm.tm_hour = hour;      // hour of day (0 .. 23)
  tm.tm_mday = day;       // day of month (0 .. 31)
  tm.tm_mon = mon - 1;     // month of year (0 .. 11)
  tm.tm_year = year - 1900; // year since 1900
  tm.tm_isdst = -1;       // determine whether daylight saving time

  std::time_t tt(std::mktime(&tm));
  assert(tt != -1);

  TimePoint date = std::chrono::system_clock::from_time_t(tt);
  date += std::chrono::seconds(int((sec - tm.tm_sec)));

  return date;
}

//-----------------------------------------------------------------------------
inline std::string asString(const TimePoint & date)
{
  std::time_t time = std::chrono::system_clock::to_time_t(date);
  std::string stringTime = ctime(&time);  // convert to calendar time
  stringTime.resize(stringTime.size() - 1);  // skip trailing newline
  return stringTime;
}

//-----------------------------------------------------------------------------
template<class StampedType, class DataType>
struct StampedWrapper
{
  StampedWrapper(StampedType stamp, DataType data)
  : stamp(stamp),
    data(data)
  {
  }

  StampedType stamp;
  DataType data;
};

//-----------------------------------------------------------------------------
template<class StampedType, class DataType>
bool operator<(
  const StampedWrapper<StampedType, DataType> & sd1,
  const StampedWrapper<StampedType, DataType> & sd2)
{
  return sd1.stamp < sd2.stamp;
}

//-----------------------------------------------------------------------------
template<class StampedType, class DataType>
bool operator>(
  const StampedWrapper<StampedType, DataType> & sd1,
  const StampedWrapper<StampedType, DataType> & sd2)
{
  return sd1.stamp > sd2.stamp;
}

}  // romea

#endif  // ROMEA_CORE_COMMON__TIME__TIME_HPP_
