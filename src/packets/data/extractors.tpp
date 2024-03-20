#include "extractors.hpp"

namespace lidar::data{
     template <std::size_t N>
     std::array<data::stl::Point, N> extract_from(const transmission::stl::Packet<N> &packet)
     {
          std::array<data::stl::Point, N> points;
          const float step = (packet.end_angle - packet.start_angle) / (N - 1);
          for (std::size_t i = 0; i < N; i++)
          {    
               points[i] = data::stl::Point(
                    (packet.start_angle + packet.)/ 100.0f,
                    distance / 1000.0f,

               );
          }

          return points;
          // step = (end_angle – start_angle)/(len – 1);
          // angle = start_angle + step*i;
          // where len is the number of measurement points in a data packet, and the value range of i is [0,len).
     }
}
