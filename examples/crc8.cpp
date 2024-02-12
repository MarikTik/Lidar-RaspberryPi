#include "packet/packet.h"
#include "packet/crc_tables.h"
#include <iostream>

// put that into main.cpp

void crc8_example() {

   lidar::Packet<12> packet;
   packet.header = lidar::frame_header_signature;
   packet.ver_len = 0x23;

   auto crc8 = lidar::verification::crc8(packet, lidar::verification::ld_19_crc_table);
   std::cout << "CRC8: " << std::hex << static_cast<int>(crc8) << std::endl;

}