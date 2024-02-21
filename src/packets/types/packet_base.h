#pragma once
#include <type_traits>
#include <cstdint>
#include <cstring>

namespace lidar::transmission {

    template<typename TPacket>
    struct PacketBase {       
        static constexpr auto uid();
        template<typename Byte, std::size_t N>
        static constexpr TPacket create(const Byte (&bytes)[N]);
    };
}

#include "packet_base.tpp"