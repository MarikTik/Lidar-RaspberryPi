#pragma once
#include <cstdint>
#include <type_traits>
#include "packet_uid.h"

namespace lidar::transmission{
     template<typename Packet>
     struct IPacketReader{
          static_assert(std::is_base_of_v<PacketUID<Packet>, Packet>, "Packet has to derive from PacketUID");
          virtual Packet read() = 0;
     };


     template<typename Packet>
     struct SerialPacketReader : public IPacketReader<Packet>
     {
          SerialPacketReader(const char* port, uint32_t baud_rate);
          Packet read() override;
     };

     template<typename Packet>
     struct GPIOPacketReader
     {
          GpioPacketReader(uint8_t rx, uint32_t baud_rate);
          Packet read() override; //not implemented
     };
     
     template<typename Packet>
     struct UdpPacketReader{
          //not implemented
     };

     template<typename Packet>
     struct TcpPacketReader{
          //not implemented
     };
     
}