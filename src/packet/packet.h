#pragma once
#include <cstdint>
#include <array>
#include <iomanip>
#include "packet_uid.h"

namespace lidar::transmission {
     static constexpr std::size_t points_per_packet_default = 12; ///< Default number of points per packet
     static constexpr std::uint8_t frame_header_signature = 0x54; ///< Signature for the frame header


     #pragma pack(push, 1)  
     /**
      * @struct Point
      * @brief Represents a single point of data from Lidar.
      */
     struct PointData {
          std::uint16_t distance; ///< Distance measurement
          std::uint8_t intensity; ///< Intensity of the reflection
     };

     /**
      * @struct Packet
      * @brief Structure for receiving packets from a Lidar.
      * 
      * @tparam points_per_frame Number of points in a single frame. Defaults to `points_per_packet_default`.
      */
     template<std::size_t points_per_frame = points_per_packet_default>
     struct Packet : public PacketUID<Packet<points_per_frame>> {
          std::uint8_t header; ///< Packet header
          std::uint8_t ver_len; ///< Version and length
          std::uint16_t speed; ///< Rotation speed
          std::uint16_t start_angle; ///< Angle at the start of the scan
          PointData points[points_per_frame]; ///< Array of Lidar points
          std::uint16_t end_angle; ///< Angle at the end of the scan
          std::uint16_t timestamp; ///< Timestamp of the packet
          std::uint8_t crc8; ///< CRC8 checksum, calculated last

          std::uint16_t uid(){
               return 0b1100001000101100;
          }
          template<std::size_t N>
          friend std::ostream& operator<<(std::ostream& os, const Packet<N>& packet);
     };
     #pragma pack(pop)
     

     // template<std::size_t N>
     // std::ostream& operator<<(std::ostream& os, const Packet<N>& packet) {
     //      os << "Header: " << static_cast<int>(packet.header)
     //         << "\nVersion-Length: " << static_cast<int>(packet.ver_len)
     //         << "\nSpeed: " << packet.speed
     //         << "\nStart Angle: " << packet.start_angle
     //         << "\nEnd Angle: " << packet.end_angle
     //         << "\nTimestamp: " << packet.timestamp
     //         << "\nCRC: " << static_cast<int>(packet.crc8) << "\nPoints:\n";
     //      for (size_t i = 0; i < N; ++i) {
     //        os << "  [" << std::setw(2) << std::setfill('0') << i << "]: "
     //           << "\nDistance: " << packet.points[i].distance
     //           << "\nIntensity: " << packet.points[i].intensity << std::endl;
     //      }
     //      return os;
     // }
   
} // namespace lidar
