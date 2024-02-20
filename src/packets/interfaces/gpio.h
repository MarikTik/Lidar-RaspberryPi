#pragma once
#include "packet_interface.h"

namespace lidar::transmission{
     template<typename Packet>
     class GpioInterface : public PacketInterface<Packet>
     {
          //not implemented
          public:
               GpioInterface(uint8_t rx, uint32_t baud_rate);
               ~GpioInterface() override;
               std::vector<Packet> read(std::size_t amount) override;
     };
}