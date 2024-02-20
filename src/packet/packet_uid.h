#pragma once
#include <type_traits>

namespace lidar::transmission {
    template<typename packet_type>
    struct PacketUID {
        //packet_type::uid has to be an integer type, i.e. uint8_t, uint16_t, ..., uint64_t and bigger types
        static_assert(std::is_invocable_v<decltype(packet_type::uid)>,   
                      "packet_type must implement a uid() method returning std::uint16_t");

        static constexpr auto uid() -> decltype(packet_type::uid()) {
            return packet_type::uid();
        }
    };
}

