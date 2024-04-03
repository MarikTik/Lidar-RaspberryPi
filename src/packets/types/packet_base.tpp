#include "packet_base.hpp"
#include <cassert>
#include <iterator>

namespace lidar::transmission{
    template <typename TPacket>
    constexpr PacketBase<TPacket>::uid_type PacketBase<TPacket>::uid() const
    {
        return static_cast<TPacket*>(this)->uid();
    }
    
    template <typename TPacket>
    constexpr bool PacketBase<TPacket>::is_valid() const
    {
        return static_cast<TPacket*>(this)->is_valid_packet();
    }
   
    template<typename TPacket>
    template<typename const_iterator>
    TPacket PacketBase<TPacket>::create(const_iterator begin, const_iterator end)
    {
        return TPacket::create(begin, end);
    }

     

}