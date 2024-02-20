#pragma once
#include "packet_reader.h"

namespace lidar::transmission{
     template<typename Packet>
     class GpioPacketReader : public PacketReader<Packet>
     {
          //not implemented
          public:
               GpioPacketReader(uint8_t rx, uint32_t baud_rate);
               ~GpioPacketReader() override;
               std::vector<Packet> read(std::size_t amount) override;
     };

}