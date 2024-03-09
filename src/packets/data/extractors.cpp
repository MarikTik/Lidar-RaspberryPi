#include "extractors.h"

namespace lidar::data{
     std::array<Point2D, 12> extract_from(const stl::Packet<12> &packet){
          std::array<Point2D, 12> points;
          for (int i = 0; i < 12; i++){
               // points[i] = Point2D(packet.angle, packet[i].distance, packet[i].intensity, packet.time_stamp);
          }
          return points;
     }
}