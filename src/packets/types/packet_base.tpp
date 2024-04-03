#include "packet_base.hpp"
#include "utilities/type_traits.hpp"
#include <cassert>
#include <cstring>
#include <iterator>

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
   
    template<typename TPacket>
    template<typename const_iterator>
    TPacket PacketBase<TPacket>::create(const_iterator begin, const_iterator end)
    {
        static_assert(utilities::is_byte_iterator_v<const_iterator>, "create() iteartors require to be byte iterators");
        TPacket packet;
        if constexpr (std::is_trivially_copyable_v<TPacket> && std::is_standard_layout_v<TPacket>) {
            std::memcpy(&packet, &(*begin), sizeof(TPacket));
        } else {
            // Use std::copy if TPacket has non-trivial or non-standard-layout members
            std::copy(begin, end, reinterpret_cast<uint8_t*>(&packet));
        }
        return packet;

    }

     

}