#pragma once
#include "packet_interface.h"

namespace lidar::transmission{

     template<typename Packet>
     class UdpInterface : public PacketInterface<Packet>{
          //not implemented
          public:
               virtual std::vector<Packet> read(std::size_t amount) override;
               virtual ~UdpInterface() override;
     };
    
}

#include "udp.tpp"