#ifndef _romea_PID_hpp_
#define _romea_PID_hpp_

#include "romea_core_common/time/Time.hpp"

namespace romea
{

class PID
{

public :

  PID(const double & kp,
      const double & ki,
      const double & kd,
      const double & imin,
      const double & imax);

  double compute(const Duration & stamp,
                 const double & setpoint,
                 const double & measurement);

  const double & kp() const;
  const double & ki() const;
  const double & kd() const;

  void reset();

private :

  void computeDt_(const Duration & stamp);

  void computeDerivative_(const double & error);

  void updateIntegral_(const double & error);

private :

  double dt_;
  double kp_;
  double ki_;
  double kd_;
  double imax_;
  double imin_;
  double i_;
  double d_;

  double previous_error_;
  Duration previous_error_stamp_;


};

}

#endif
