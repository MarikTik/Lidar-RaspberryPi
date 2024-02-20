#pragma once
#include <type_traits>

namespace lidar::transmission {

    template<typename packet_type>
    struct PacketBase {       
        static constexpr auto uid() {
            static_assert(
                std::is_integral_v<decltype(packet_type::uid())>,   
                "packet_type must implement a `uid` method and return an integral type"
            );

            return packet_type::uid();
        }
    };
}

//   return 0b1100001000101100;