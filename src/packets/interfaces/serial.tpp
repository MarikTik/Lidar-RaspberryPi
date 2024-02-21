#include "serial.h"
#include <pigpio.h>
#include <string.h>
namespace lidar::transmission{
      template<typename Packet>
      SerialInterface<Packet>::SerialInterface(const char* port, uint32_t baud_rate) 
         : _handle(serOpen(const_cast<char*>(port), baud_rate, 0))
      {    
      }
 
      template<typename Packet>
      SerialInterface<Packet>::~SerialInterface() 
      {    
         serClose(_handle);
      }
     
      template<typename Packet>
      std::vector<Packet> SerialInterface<Packet>::read(std::size_t amount) {
         std::vector<Packet> packets;
         packets.reserve(amount);

         uint16_t packet_size = sizeof(Packet);
         int8_t beginning[packet_size];

         auto read_till_success = [&](int8_t* destination, unsigned size){ 
            int bytes_read = 0;
            while(bytes_read != packet_size) bytes_read = serRead(_handle, destination, size);
         }
         
         read_till_success(beginning, packet_size);
         
         uint16_t offset = PacketInterface<Packet>::offset(beginning);

         if (!offset){
            packets.push(Packet::create(beginning))
         }
         else{
            uint16_t rest_size;
            if (offset >= packet_size / 2)
            else rest_size = packet_size - offset;
            int8_t* rest = new int8_t[rest_size];
            const auto uid_size = sizeof(decltype(Packet::uid()))
            read_till_success(rest, packet_size);
            memmove(beginning, beginning + offset - uid_size, )
             
         }
      
         return packets;  
      }
}