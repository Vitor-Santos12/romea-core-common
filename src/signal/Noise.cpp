//local
#include "romea_common/signal/Noise.hpp"

//std
#include <cmath>

namespace romea{

double convertNoiseDensityToNoiseStd(const double & noiseDensity,
                                     const double & frequency)
{
    return 1.57*noiseDensity*std::sqrt(frequency);
}

}
