#pragma once
#include "async_interface.hpp"
#include <boost/asio/io_context.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <shared_mutex>
#include <condition_variable>

using namespace boost;

class SerialInterface;

template<>
struct ConnectionSettings<SerialInterface>{
     unsigned int baud_rate;
     unsigned int character_size;
     asio::serial_port_base::stop_bits::type stop_bits;
     asio::serial_port_base::parity::type parity;
     asio::serial_port_base::flow_control::type flow_control;
};

class SerialInterface : public AsyncInterface<SerialInterface>{
     using connection_settings = ConnectionSettings<SerialInterface>;
public:
     SerialInterface(boost::asio::io_context& io_context);
     template<typename Data>
     std::vector<Data> async_read() const;
     void async_scan();
     bool is_open() const;
     bool open(const std::string& port);
     void close();

private:
     boost::asio::serial_port _serial_port;
     connection_settings _connection_settings;

     mutable std::shared_mutex _mutex;
     mutable std::condition_variable _cv;

};


SerialInterface::SerialInterface(asio::io_context &io_context)
     : AsyncInterface<SerialInterface>(io_context), _serial_port(io_context)
{
}

bool SerialInterface::open(const std::string& port)
{
     system::error_code ec;
     if (_serial_port.is_open()){
          std::cerr << "Error: Lidar is already opened. Closing the old one and opening " << port << "\n"; 
          close();
     }
     _serial_port.open(port, ec);
     if (ec) 
     {
          std::cerr << "Error from open: " << ec.message() << std::endl;
          return false;
     }
    
     _serial_port.set_option(boost::asio::serial_port_base::baud_rate(_connection_settings.baud_rate), ec);
     _serial_port.set_option(boost::asio::serial_port_base::character_size(_connection_settings.character_size), ec);
     _serial_port.set_option(boost::asio::serial_port_base::stop_bits(_connection_settings.stop_bits), ec);
     _serial_port.set_option(boost::asio::serial_port_base::parity(_connection_settings.parity), ec);
     _serial_port.set_option(boost::asio::serial_port_base::flow_control(_connection_settings.flow_control), ec);

     if (ec) 
     {
          std::cerr << "Error from setting options: " << ec.message() << std::endl;
          close();
          return false;
     }
     return true;
}

void SerialInterface::close()
{
     if (_serial_port.is_open())
          _serial_port.close();
}

bool SerialInterface::is_open() const
{
     return _serial_port.is_open();
}
template<typename Data> std::vector<Data> SerialInterface::async_read() const
{
}

void SerialInterface::async_scan()
{
}

 


