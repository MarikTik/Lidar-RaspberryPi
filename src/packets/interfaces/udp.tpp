#pragma once
#include "udp.h"

namespace lidar::transmission{
     template <typename Packet>
     std::vector<Packet> UdpInterface<Packet>::read(std::size_t amount)
     {
          return std::vector<Packet>();
     }
     template <typename Packet>
     UdpInterface<Packet>::~UdpInterface()
     {
     }

}