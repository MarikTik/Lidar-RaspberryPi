extern "C" {
#include <pigpio.h>
}

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
// #include "packet/packet.h"
// #include "packet/packet_reader.h"

int main() {
    // Initialize pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialisation failed." << std::endl;
        return 1;
    }
   
  
    // Open serial device
    char* portname = const_cast<char*>("/dev/ttyUSB0");
    int serHandle = serOpen(portname, 230400, 0);
    if (serHandle < 0) {
        std::cerr << "Failed to open serial port." << std::endl;
        gpioTerminate();
        return 1;
    }
     std::this_thread::sleep_for(std::chrono::milliseconds(100));
    // Read 50 8-byte packets
    for (int i = 0; i < 10000; ++i) {
           for (int j = 0; j < 8; j++){
                auto byte = serReadByte(serHandle);
                std::cout << std::hex << byte;
            }
             
        // char buf[8];
        // auto ret = serRead(serHandle, buf, sizeof(buf));
        // if (ret == sizeof(buf)) {
        //     std::cout << "Packet " << (i + 1) << ": ";
        //     for (char byte : buf) {
        //         std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)(unsigned char)byte << " ";
        //     }
        //     std::cout << std::dec << std::endl; // Switch back to decimal for regular output
        // } else {
        //     std::cerr << "Failed to read the expected amount of data. return value: " << ret << std::endl;
        //     break; // Exit if we fail to read the expected number of bytes
        // }
    }

    // Close the serial port
    serClose(serHandle);

    // Cleanup pigpio
    gpioTerminate();

    return 0;
}
