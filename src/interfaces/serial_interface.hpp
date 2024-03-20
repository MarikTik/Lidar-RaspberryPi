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
     void set_buffer_size(std::size_t size);
     
private:
     boost::asio::serial_port _serial_port;
     connection_settings _connection_settings;

     std::vector<uint8_t> _buffer;
     mutable std::shared_mutex _mutex;
     mutable std::condition_variable _cv;
};

#include "serial_interface.tpp"
 


