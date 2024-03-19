#pragma once
#include <cstdint>
#include <boost/units/systems/si/frequency.hpp>
#include <boost/units/systems/angle/degrees.hpp>
#include <boost/units/systems/si/io.hpp>
#include <boost/asio/serial_port.hpp>

using namespace boost;
 

class Lidar
{
     using rotation_frequency = units::quantity<units::si::frequency>;
     public:
          Lidar(asio::io_context &io_context);
          virtual ~Lidar();

          void begin(const std::string &port, uint32_t baud_rate);
          virtual void close();
          void set_frequency(const rotation_frequency new_frequency);
 
          
     private:
          asio::io_context& _io_context;
          asio::serial_port _serial_port;
          rotation_frequency _rotation_frequency;
          uint32_t _baud_rate;
};
