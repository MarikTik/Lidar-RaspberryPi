#pragma once
#include <cstdint>


namespace lidar{
     static constexpr std::size_t measurements_per_frame_default = 12;
     static constexpr std::uint8_t frame_header_signature = 0x54;

     #pragma pack(push, 1)  

     struct Measurement{
          std::uint16_t distance;
          std::uint16_t angle;
     };

     template<std::size_t measurements_per_frame = measurements_per_frame_default>
     struct Frame{
          std::uint8_t header;
          std::uint8_t verLen;
          std::uint16_t speed;
          std::uint16_t startAngle;
          lidar::Measurement measurments[measurements_per_frame];
          std::uint16_t endAngle;
          std::uint16_t timestamp;
          std::uint8_t crc8; // This field is filled last, after CRC calculation
     };

     #pragma pack(pop)
}