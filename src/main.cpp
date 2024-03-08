
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
// #include "packet/packet.h"
// #include "packet/packet_reader.h"

int main() {
  
    SerialStream serial;
    serial.open("/dev/ttyUSB0", 230400);
    
    uint8_t buffer[1024];
    serial.read(buffer, 1024);

    for (int i = 0; i < 1024; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i] << " ";
    }
    return 0;
}
