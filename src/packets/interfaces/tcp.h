#pragma once
#include "packet_interface.h"

namespace lidar::transmission{
 
     template<typename Packet>
     class TcpInterface : public PacketInterface<Packet>{
          //not implemented
          public:
               virtual std::vector<Packet> read(std::size_t amount) override;
               virtual ~TcpInterface() override;
     };
}

#include "tcp.tpp"