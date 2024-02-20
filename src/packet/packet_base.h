#pragma once
#include <type_traits>

namespace lidar::transmission {
    template<typename packet_type>
    struct PacketBase {
        //packet_type::uid has to be an integer type, i.e. uint8_t, uint16_t, ..., uint64_t and bigger types
       
        static constexpr auto header() {
            static_assert(
                std::is_integral_v<decltype(packet_type::header())>,   
                "packet_type must implement a uid() method returning an integral type"
            );

            return packet_type::header();
        }
    };
}

