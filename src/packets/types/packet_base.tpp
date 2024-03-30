#include "packet_base.hpp"
#include <cassert>
namespace lidar::transmission{
    template <typename TPacket>
    constexpr auto PacketBase<TPacket>::uid()
    {
        static_assert(
            std::is_integral_v<decltype(TPacket::uid())>,   
            "packet_type must implement a `uid` method and return an integral type"
        );   
        return TPacket::uid();
    }
    
    template <typename TPacket>
    bool PacketBase<TPacket>::is_valid_packet()
    {
        static_assert(
            std::is_same_v<decltype(TPacket::is_valid_packet()), bool>,
            "packet_type must implement a `is_valid_packet` method and return a boolean"
        );
        return TPacket::is_valid_packet();
    }

    template <typename TPacket>
    template<typename Container, typename>
    TPacket PacketBase<TPacket>::create(const Container& raw_packet)
    {
        using value_type = typename Container::value_type;

        assert(sizeof(TPacket) == raw_packet.size() * sizeof(value_type));
        TPacket packet;
        std::copy(raw_packet.begin(), raw_packet.end(), reinterpret_cast<value_type*>(&packet));
        return packet;
    }

}