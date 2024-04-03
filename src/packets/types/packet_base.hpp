#pragma once
#include <cstdint>
#include <type_traits>
#include "utilities/type_traits.hpp"

namespace lidar::transmission {

    using namespace lidar;
    template<typename TPacket>
    struct PacketBase {
        using uid_type = decltype(std::declval<TPacket>().uid());

        constexpr uid_type uid() const;
        bool is_valid() const;
               
        template<typename const_iterator>
        static TPacket create(const_iterator begin, const_iterator end);
    };
    
}

#include "packet_base.tpp"