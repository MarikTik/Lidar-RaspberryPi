#pragma once
#include <cstdint>
#include "packet_base.hpp"

/// @brief /stl packets work with any of the followign models: STL-27L, STL-19-P, STL-26N, STL-06P, STL-26
namespace lidar::transmission::stl {
     static constexpr std::size_t points_per_packet_default = 12; ///< Default number of points per packet

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
      * @tparam N Number of points in a single frame. Defaults to `points_per_packet_default`.
      */
     template<std::size_t N = points_per_packet_default>
     struct Packet 
          : public PacketBase<Packet<N>>,
            public StlPacketBase<Packet<N>>
          {
          std::uint8_t header; ///< Packet header
          std::uint8_t ver_len; ///< Version and length
          std::uint16_t speed; ///< Rotation speed
          std::uint16_t start_angle; ///< Angle at the start of the scan
          PointData points[N]; ///< Array of Lidar points
          std::uint16_t end_angle; ///< Angle at the end of the scan
          std::uint16_t timestamp; ///< Timestamp of the packet
          std::uint8_t crc8; ///< CRC8 checksum, calculated last

          
          static constexpr std::uint16_t uid(){
               constexpr std::uint8_t header_signature = 0x54;  
               constexpr std::uint8_t ver_len_signature = 0x2C;

               return static_cast<uint16_t>(header_signature) << 8 | ver_len_signature; 
          }
          
     };
     #pragma pack(pop)

}
