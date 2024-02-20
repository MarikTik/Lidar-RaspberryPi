#include "gpio.h"

namespace lidar::transmission{
     template <typename Packet>
     GpioInterface<Packet>::GpioInterface(uint8_t rx, uint32_t baud_rate)
     {
     }

     template <typename Packet>
     GpioInterface<Packet>::~GpioInterface()
     {
     }
     template <typename Packet>
     std::vector<Packet> GpioInterface<Packet>::read(std::size_t amount)
     {
          return std::vector<Packet>();
     }
}