#include "serial_reader.h"

namespace lidar::transmission{
     template<typename Packet>
     SerialPacketReader<Packet>::SerialPacketReader(const char* port, uint32_t baud_rate) 
        : _serial_handle(serOpen(const_cast<char*>(port), baud_rate, 0))
     {    
     }

     template<typename Packet>
     SerialPacketReader<Packet>::~SerialPacketReader() 
     {    
        serClose(_serial_handle);
     }
    
     template<typename Packet>
     std::vector<Packet> SerialPacketReader<Packet>::read(std::size_t amount) {
         std::vector<Packet> packets;
         packets.reserve(amount);
         
         const auto packet_size = sizeof(Packet);
 
         std::array<uint8_t, packet_size> first_read;
         serRead(_serial_handle, first_read, packet_size);
         return packets;  
     }
}