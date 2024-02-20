#pragma once
#include <type_traits>

namespace lidar::transmission {
    
    template<typename packet_type>
    struct PacketBase {       
        static constexpr auto header() {
            static_assert(
                std::is_integral_v<decltype(packet_type::header())>,   
                "packet_type must implement a `header` method and return an integral type"
            );

            return packet_type::header();
        }
    };
}

