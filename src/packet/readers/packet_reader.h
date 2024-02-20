#pragma once
#include <cstdint>
#include <type_traits>
#include <vector>
#include <array>
#include "../packet_base.h"


namespace lidar::transmission{
     template<typename Packet>
     class PacketReader{
          static_assert(std::is_base_of_v<PacketUID<Packet>, Packet>, "Packet has to derive from PacketUID");
          public:
               virtual std::vector<Packet> read(std::size_t amount) = 0;
               virtual ~PacketReader() = 0;

          protected:
               static std::uint16_t packet_start(const std::array<std::uint8_t, sizeof(Packet)>& raw_bytes){ // the first input of size Packet 
                    const uid_t uid = Packet::uid(); //sequence of bytes that mark the beginning of the packet
                    uid_t bytes;

                    for (auto i = 0; i < raw_bytes.size(); i++){
                        (bytes <<= 8) |= raw_bytes[i];
                        if (bytes == uid) return i;
                    }
                    return 65535; // not found, in the future will add error indication
               }  
     };
}
