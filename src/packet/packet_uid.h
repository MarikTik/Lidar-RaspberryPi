#pragma once
#include <type_traits>

namespace lidar::transmission{
     template<typename packet_type, typename = std::void_t<>>
     struct PacketUID; // Forward declaration to make the specialization the primary template.
     
     //unique identifier for packets
     template<typename packet_type>
     struct PacketUID <packet_type, std::void_t<decltype(std::declval<packet_type>().uid())>>
     { 
          auto uid() -> decltype(static_cast<packet_type*>(this)->uid()){
               return static_cast<packet_type*>(this)->uid();
          }
     };
}

