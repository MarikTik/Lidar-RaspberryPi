#pragma once
#include <cstdint>
#include <array>

namespace lidar{
     static constexpr std::size_t points_per_packet_default = 12;
     static constexpr std::uint8_t frame_header_signature = 0x54;

     #pragma pack(push, 1)  

     struct Point{
          std::uint16_t distance;
          std::uint16_t intensity;
     };

     template<std::size_t points_per_frame = points_per_packet_default>
     struct Packet{
          std::uint8_t header;
          std::uint8_t ver_len;
          std::uint16_t speed;
          std::uint16_t start_angle;
          lidar::Point points[points_per_frame];
          std::uint16_t end_angle;
          std::uint16_t timestamp;
          std::uint8_t crc8; // This field is filled last, after CRC calculation
     };

     #pragma pack(pop)
     
     template<typename packet_type = Packet<12>, std::size_t crc_table_size>
     std::uint8_t crc8(packet_type packet, std::array<std::uint8_t, crc_table_size>& crc_table) {
          std::uint8_t* packet_bits = reinterpret_cast<std::uint8_t*>(&packet);
          std::uint8_t crc = 0;
          std::uint8_t data_bits_length = sizeof(packet_type) - sizeof(packet.crc8);

          for (uint16_t i = 0; i < data_bits_length; i++) 
               crc = crc_table[(crc ^ *(packet_bits++)) & 0xff];

          return crc;
     }
 

   
}