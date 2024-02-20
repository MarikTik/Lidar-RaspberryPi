#pragma once
#include "packet_reader.h"

namespace lidar::transmission{
 
     template<typename Packet>
     class TcpPacketReader : public PacketReader<Packet>{
          //not implemented
          virtual std::vector<Packet> read(std::size_t amount) override;
          virtual ~TcpPacketReader() override;
     };

  

}