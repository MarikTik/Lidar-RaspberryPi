#include "tcp_reader.h"
namespace lidar::transmission{
     template <typename Packet>
     inline std::vector<Packet> TcpPacketReader<Packet>::read(std::size_t amount)
     {
          return std::vector<Packet>();
     }

     template <typename Packet>
     inline TcpPacketReader<Packet>::~TcpPacketReader()
     {
     }
}
