#pragma once
#include <cstdint>
#include <type_traits>
#include "packet_uid.h"
#include <cstdint>

namespace lidar::transmission{
     template<typename Packet>
     struct IPacketReader{
          static_assert(std::is_base_of_v<PacketUID<Packet>, Packet>, "Packet has to derive from PacketUID");
          virtual Packet read(std::size_t packets) = 0;
     };


     template<typename Packet>
     class SerialPacketReader : public IPacketReader<Packet>
     {
          public:
               SerialPacketReader(const char* port, uint32_t baud_rate);
               Packet read(std::size_t packets) override;


     };

     template<typename Packet>
     class GPIOPacketReader
     {
          GpioPacketReader(uint8_t rx, uint32_t baud_rate);
          Packet read(std::size_t packets) override; //not implemented
     };
     
     template<typename Packet>
     class UdpPacketReader{
          //not implemented
     };

     template<typename Packet>
     class TcpPacketReader{
          //not implemented
     };
     
     
}

#include "packet_reader.tpp"