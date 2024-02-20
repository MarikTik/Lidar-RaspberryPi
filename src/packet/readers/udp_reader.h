#pragma once
#include "packet_reader.h"

namespace lidar::transmission{

     template<typename Packet>
     class UdpPacketReader : public PacketReader<Packet>{
          //not implemented
          public:
               virtual std::vector<Packet> read(std::size_t amount) override;
               virtual ~UdpPacketReader() override;
     };
    
}
