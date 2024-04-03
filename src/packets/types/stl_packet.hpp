#pragma once
#include <cstdint>
#include "packet_base.hpp"

/// @brief /stl packets work with any of the followign models: STL-27L, STL-19-P, STL-26N, STL-06P, STL-26
namespace lidar::transmission::stl {


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
      * @tparam N Number of points in a single frame.
      */
     template<std::size_t N>
     struct Packet : public PacketBase<Packet<N>>
     {
          std::uint8_t header; ///< Packet header
          std::uint8_t ver_len; ///< Version and length
          std::uint16_t speed; ///< Rotation speed
          std::uint16_t start_angle; ///< Angle at the start of the scan
          PointData points[N]; ///< Array of Lidar points
          std::uint16_t end_angle; ///< Angle at the end of the scan
          std::uint16_t timestamp; ///< Timestamp of the packet
          std::uint8_t crc8; ///< CRC8 checksum, calculated last

          
          constexpr std::uint16_t uid() const;
          bool is_valid() const;          
     };
     #pragma pack(pop)
   
}

#include "stl_packet.tpp"
