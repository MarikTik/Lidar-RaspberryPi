#pragma once
#include <cstdint>
#include <cmath>
#include "../types/stl_packet.hpp"

namespace lidar::data::stl{
     using namespace transmission::stl;
     struct Point{ 
          float angle; //radians (0-2π)
          uint16_t distance; //millimeters
          uint8_t intensity; // 0-255

          inline float x();
          inline float y();
          
          // angle in range 0-36000, distance in mm, intensity 0-255
          constexpr Point(float angle, uint16_t distance, uint8_t intensity);

          Point() = default;
          struct SuppliedData{
               float angular_speed; //radians per second
               uint16_t timestamp; //milliseconds

               template<size_t N>
               constexpr SuppliedData(const Packet<N>& packet);
          };
     };

     inline float Point::x(){
          return distance * cos(angle);
     }

     inline float Point::y()
     {
          return distance * sin(angle);
     }
     
     inline constexpr Point::Point(float angle, uint16_t distance, uint8_t intensity)
          : angle(angle * (M_PI / 18000.f)), distance(distance), intensity(intensity)
     {
     }
   
     template <size_t N>
     inline constexpr Point::SuppliedData::SuppliedData(const Packet<N> &packet)
          : angular_speed(packet.speed / (M_PI / 18000.f)), timestamp(packet.timestamp)
     {
     }

   

}
