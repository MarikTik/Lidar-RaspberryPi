#pragma once
#include <cstdint>
#include <cmath>

namespace lidar::data::stl{
     using namespace std;
     
     
     struct Point{ 
          
          float angle; //degrees
          uint16_t distance; //millimeters
        
          uint8_t intensity; 

          inline float x();
          inline float y();

          Point() = default;
          constexpr Point(float angle, uint16_t distance, uint8_t intensity);

          struct SuppliedData{
               uint16_t angular_speed; //degrees per second
               uint16_t timestamp; //milliseconds
               SuppliedData() = default;
               constexpr SuppliedData(uint16_t angular_speed, uint16_t timestamp);
          };
     };

     inline float Point::x(){

          return distance * cos(angle * M_PI / 180.0f);
     }

     inline float Point::y()
     {
          return distance * sin(angle * M_PI / 180.0f);
     }
     
     
     constexpr Point::Point(float angle, uint16_t distance, uint8_t intensity)
          : angle(angle), distance(distance), intensity(intensity)
     {
     }
     constexpr Point::SuppliedData::SuppliedData(uint16_t angular_speed, uint16_t timestamp)
          : angular_speed(angular_speed), timestamp(timestamp)
     {
     }
}

