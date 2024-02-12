#pragma once
#include <cstdint>


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
}