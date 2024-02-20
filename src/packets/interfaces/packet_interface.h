#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>
#include <array>
#include "../types/packet_base.h"


namespace lidar::transmission{
     template<typename Packet>
     class PacketInterface{
          static_assert(std::is_base_of_v<PacketInterface<Packet>, Packet>, "Packet has to derive from PacketUID");
          public:
               virtual std::vector<Packet> read(std::size_t amount) = 0;
               virtual ~PacketInterface() = 0;

          protected:
               static std::uint16_t packet_start(const std::array<std::uint8_t, sizeof(Packet)>& raw_bytes); // the first input of size Packet 
     };
}

#include "packet_interface.tpp"