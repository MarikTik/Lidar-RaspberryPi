#pragma once
#include <cstdint>
#include <array>
#include "crc_tables.h"

namespace lidar {
     /**
      * @brief Namespace for verification-related functionality
      */
     namespace verification {
          /**
           * @brief Calculates the CRC8 checksum for a given packet using a specified CRC table.
           * 
           * @tparam packet_type Type of the packet for which CRC is being calculated.
           * @tparam crc_table_size Size of the CRC table.
           * @param packet Reference to the packet object.
           * @param crc_table The CRC table used for calculating the CRC8 checksum.
           * @return std::uint8_t The calculated CRC8 checksum.
           */
          template<typename packet_type, std::size_t crc_table_size>
          std::uint8_t crc8(packet_type& packet, const std::array<std::uint8_t, crc_table_size>& crc_table);
     }

     static constexpr std::size_t points_per_packet_default = 12; ///< Default number of points per packet
     static constexpr std::uint8_t frame_header_signature = 0x54; ///< Signature for the frame header

     #pragma pack(push, 1)  

     /**
      * @struct Point
      * @brief Represents a single point of data from Lidar.
      */
     struct Point {
          std::uint16_t distance; ///< Distance measurement
          std::uint16_t intensity; ///< Intensity of the reflection
     };

     /**
      * @struct Packet
      * @brief Structure for receiving packets from a Lidar.
      * 
      * @tparam points_per_frame Number of points in a single frame. Defaults to `points_per_packet_default`.
      */
     template<std::size_t points_per_frame = points_per_packet_default>
     struct Packet {
          std::uint8_t header; ///< Packet header
          std::uint8_t ver_len; ///< Version and length
          std::uint16_t speed; ///< Rotation speed
          std::uint16_t start_angle; ///< Angle at the start of the scan
          lidar::Point points[points_per_frame]; ///< Array of Lidar points
          std::uint16_t end_angle; ///< Angle at the end of the scan
          std::uint16_t timestamp; ///< Timestamp of the packet
          std::uint8_t crc8; ///< CRC8 checksum, calculated last

          /**
           * @brief Checks if the packet is intact (no corruption detected).
           * 
           * @return true If the packet is intact.
           * @return false If corruption is detected in the packet.
           */
          bool intact() const {
               return crc8 == verification::crc8(*this, verification::ld_19_crc_table);
          }
     };

     #pragma pack(pop)
     
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
} // namespace lidar
