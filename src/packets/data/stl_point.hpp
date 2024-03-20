#pragma once
#include <cstdint>
#include <cmath>

namespace lidar::data::stl{
     using namespace std;

     struct Point{ 
          float angle;
          uint16_t distance;
          uint8_t intensity;
          uint16_t time_stamp; 

          inline float x();
          inline float y();

          Point() = default;
          constexpr Point(float angle, uint16_t distance, uint8_t intensity, uint64_t stamp);
          
     };

     inline float Point::x(){

          return distance * cos(angle * M_PI / 180.0f);
     }

     inline float Point::y()
     {
          return distance * sin(angle * M_PI / 180.0f);
     }

     constexpr Point::Point(float angle, uint16_t distance, uint8_t intensity, uint64_t stamp)
          : angle(angle), distance(distance), intensity(intensity), time_stamp(stamp)
     {
     }
}

