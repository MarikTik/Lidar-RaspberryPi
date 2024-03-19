#pragma once
#include <cstdint>
#include <type_traits>
#include "utilities/type_traits.hpp"

namespace lidar::transmission {

    using namespace lidar;
    template<typename TPacket>
    struct PacketBase {       
        static constexpr auto uid();

        template<typename Container, typename = std::enable_if_t<
                                                                 utilities::is_iterable_v<Container> and
                                                                 std::is_trivially_copyable_v<typename Container::value_type> 
                                                                >
                > 
        static TPacket create(const Container& raw_packet);
    
    };
    
}

#include "packet_base.tpp"