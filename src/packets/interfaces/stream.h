#pragma once
#include <istream>
#include "packet_interface.h"

namespace lidar::transmission{
     template<typename Packet>
     class StreamInterface : public PacketInterface<Packet>{
          public:
               StreamInterface(std::istream& is);
               ~StreamInterface() override;
               std::vector<Packet> read(std::size_t amount) override;
          private:
               std::istream& _is;
     };
}

#include "stream.tpp"