#pragma once
#include "packet_interface.h"

namespace lidar::transmission{
     template<typename Packet>
     class SerialInterface : public PacketInterface<Packet>
     {
          public:
               SerialInterface(const char* port, uint32_t baud_rate);
               ~SerialInterface() override;
               std::vector<Packet> read(std::size_t amount) override;
          private:
               std::int16_t _serial_handle;
     };
}
  
#include "serial.tpp"
  


     
    

