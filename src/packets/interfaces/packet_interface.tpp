#include "packet_interface.h"

namespace lidar::transmission{
     template <typename Packet>
     std::uint16_t PacketInterface<Packet>::packet_start(const std::array<std::uint8_t, sizeof(Packet)> &raw_bytes)
     {
          const uid_t uid = Packet::uid(); //sequence of bytes that mark the beginning of the packet
          uid_t bytes;

          for (auto i = 0; i < raw_bytes.size(); i++){
              (bytes <<= 8) |= raw_bytes[i];
              if (bytes == uid) return i;
          }
          return 65535; // not found, in the future will add error indication
     }
}