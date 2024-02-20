#pragma once
#include <type_traits>

namespace lidar::transmission {
    template<typename packet_type>
    struct PacketUID {
        static_assert(std::is_invocable_r_v<std::uint16_t, decltype(&packet_type::uid), packet_type>, 
                      "packet_type must implement a uid() method returning std::uint16_t");

        static constexpr auto uid() -> decltype(packet_type::uid()) {
            return packet_type::uid();
        }
    };
}

