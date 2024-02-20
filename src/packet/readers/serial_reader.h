#pragma once
#include "packet_reader.h"

namespace lidar::transmission{
     template<typename Packet>
     class SerialPacketReader : public PacketReader<Packet>
     {
          public:
               SerialPacketReader(const char* port, uint32_t baud_rate);
               ~SerialPacketReader() override;
               std::vector<Packet> read(std::size_t amount) override;
          private:
               std::int16_t _serial_handle;
     };
}
  
  


     
    

