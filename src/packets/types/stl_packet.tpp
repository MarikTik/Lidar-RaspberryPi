#include "stl_packet.hpp"
#include "../verification/crc8/algorithm.hpp"
#include "../verification/crc8/ld19.hpp"




namespace lidar::transmission::stl{
     template <std::size_t N>
     constexpr std::uint16_t Packet<N>::uid() const
     {
          constexpr std::uint8_t header_signature = 0x54;  
          constexpr std::uint8_t ver_len_signature = 0x2C;
          return static_cast<uint16_t>(header_signature) << 8 | ver_len_signature; 
     }
     
     using namespace lidar::verification;

     template<>
     bool Packet<12>::is_valid() const
     {
          return lidar::verification::crc8(*this, ld19::crc_table) == this->crc8;
     }

}




 