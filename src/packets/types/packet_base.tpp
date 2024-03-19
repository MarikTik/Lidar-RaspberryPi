#include "packet_base.h"

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
     

    template<typename TPacket>
    template<typename Byte, std::size_t N>
    inline constexpr TPacket PacketBase<TPacket>::create(const Byte(& bytes)[N])
    {
        static_assert(
            std::is_same_v<Byte, uint8_t> || std::is_same_v<Byte, int8_t>,
            "create only accepts 8-bit sequences, either uint8_t or int8_t."    
        );
        static_assert(
            N == sizeof(TPacket),
            "The size of the passed bytes array should exactly match the size of TPacket."
        );
        static_assert(
            std::is_trivially_copyable_v<TPacket>,
            "TPacket must be trivially copyable."
        );
        // no checks for endianess!

        TPacket packet;
        std::memcpy(&packet, bytes, sizeof(TPacket)); 
        return packet;
    }

}