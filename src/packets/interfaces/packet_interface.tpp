#include "packet_interface.h"

namespace lidar::transmission{
     template <typename Packet>
     template <typename Byte, size_t N>
     inline std::uint16_t PacketInterface<Packet>::offset(const Byte (&bytes)[N]) //implementation assumes little endianness
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
          uid_t group = 0;

          //1 byte uid = 0x54: 0x54 0x3 0x5 0x10 0xFF 0xBB 0xAA 0x3E 
          //2 byte uid = 0x54 0x2C: 0x54 0x2C 0x5 0x10 0xFF 0xBB 0xAA 0x3E
          for (uint16_t i = 0; i < N; i++){ 
              (group <<= 8) |= bytes[i];
              if (group == uid) return i - sizeof(uid_t) + 1;
          }
          
          return UINT16_MAX; // not found, in the future will add error indication
     }
    
}