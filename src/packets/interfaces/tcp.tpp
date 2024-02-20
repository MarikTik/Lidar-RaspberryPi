#include "tcp.h"

namespace lidar::transmission{
     template <typename Packet>
     inline std::vector<Packet> TcpInterface<Packet>::read(std::size_t amount)
     {
          return std::vector<Packet>();
     }

     template <typename Packet>
     inline TcpInterface<Packet>::~TcpInterface()
     {
     }
}
