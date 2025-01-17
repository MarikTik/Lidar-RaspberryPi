#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>
#include <array>
#include "../types/packet_base.h"


namespace lidar::transmission{
     template<typename Packet>
     class PacketInterface{
          static_assert(std::is_base_of_v<PacketBase<Packet>, Packet>, "Packet has to derive from PacketBase");
          public:
               virtual std::vector<Packet> read(std::size_t amount) = 0;
               virtual ~PacketInterface() {};

          protected:
               template<typename Byte, size_t N>
               static std::uint16_t offset(const Byte (&bytes)[N]); // the first input of size Packet 
     };

}

#include "packet_interface.tpp"