#include "point2d.h"
#include <cmath>

namespace lidar::data{

     Point2D::Point2D(double x, double y, uint8_t intensity, uint64_t stamp) 
          : x(x), y(y), intensity(intensity), time_stamp(stamp),
          distance(sqrt(x * x + y * y)), angle(atan2(y, x))
     {
     }

      Point2D::Point2D(float angle, uint16_t distance, uint8_t intensity, uint64_t stamp)
          : angle(angle), distance(distance), intensity(intensity), time_stamp(stamp),
          x(distance * cos(angle)), y(distance * sin(angle))
     {
     }

      Point2D::Point2D(double x, double y, float angle, uint16_t distance, uint8_t intensity, uint64_t stamp)
          : x(x), y(y), angle(angle), distance(distance), intensity(intensity), time_stamp(stamp)
     {
     }
}

