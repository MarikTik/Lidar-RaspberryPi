#pragma once
#include <array>
#include <cstdint>

namespace lidar::tansmission::verification{
     namespace verification {
        template<typename packet_type, std::size_t crc_table_size>
        std::uint8_t crc8(packet_type& packet, const std::array<std::uint8_t, crc_table_size>& crc_table) {
             std::uint8_t* packet_bits = reinterpret_cast<std::uint8_t*>(&packet);
             std::uint8_t crc = 0;
             std::uint8_t data_bits_length = sizeof(packet_type) - sizeof(packet.crc8);
             for (std::uint16_t i = 0; i < data_bits_length; i++) 
                  crc = crc_table[(crc ^ *(packet_bits++)) & 0xff];
             return crc;
          }
     }
}