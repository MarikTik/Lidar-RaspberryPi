#include "packet_interface.h"

namespace lidar::transmission{
     template <typename Packet>
     template <typename Byte, size_t N>
     inline std::uint16_t PacketInterface<Packet>::offset(const Byte (&bytes)[N])
     {
          static_assert(
              std::is_same_v<Byte, uint8_t> || std::is_same_v<Byte, int8_t>,
              "packet_start only accepts 8-bit sequences, either uint8_t or int8_t."    
          );
          static_assert(
               N == sizeof(Packet),
              "The size of the passed bytes array should exactly match the size of Packet."
          );
          using uid_t = decltype(Packet::uid());
          
          const uid_t uid = Packet::uid(); //sequence of bytes that mark the beginning of the packet
          uid_t group;

          for (uint16_t i = 0; i < N; i++){
              (group <<= 8) |= bytes[i];
              if (group == uid) return i + sizeof(uid_t);
          }
          
          return UINT16_MAX; // not found, in the future will add error indication
     }
    
}