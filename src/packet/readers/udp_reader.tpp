#pragma once
#include "udp_reader.h"

namespace lidar::transmission{
     template <typename Packet>
     std::vector<Packet> UdpPacketReader<Packet>::read(std::size_t amount)
     {
          return std::vector<Packet>();
     }
     template <typename Packet>
     UdpPacketReader<Packet>::~UdpPacketReader()
     {
     }

}