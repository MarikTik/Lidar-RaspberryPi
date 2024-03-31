#include "packet_base.hpp"
#include <cassert>
namespace lidar::transmission{
    template <typename TPacket>
    constexpr auto PacketBase<TPacket>::uid() const
    {
        return static_cast<TPacket*>(this)->uid();
    }
    
    template <typename TPacket>
    bool PacketBase<TPacket>::is_valid() const
    {
        return static_cast<TPacket*>(this)->is_valid_packet();
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