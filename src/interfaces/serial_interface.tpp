#include "serial_interface.hpp"
#include <boost/system/error_code.hpp>


SerialInterface::SerialInterface(asio::io_context &io_context)
     : AsyncInterface<SerialInterface>(io_context), _serial_port(io_context)
{
     set_buffer_size(47 * 500); //!Will be removed later; represents one full rotation of LD19-lidar
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

void SerialInterface::set_buffer_capacity(std::size_t size)
{
     _scan_buffer.set_capacity(size);
}

void SerialInterface::async_scan()
{
     uint8_t buffer[1024];
     static auto read_handler = [this, &buffer](const system::error_code& ec, std::size_t bytes_transferred)
     {
          if(ec){ 
               std::cerr << "Error: " << ec.message() << "\n";
               return;
          }
          else{
               std::unique_lock<std::shared_mutex> lock(_mutex);
               for (std::size_t i = 0; i < bytes_transferred; ++i)
                    _scan_buffer.push_back(buffer[i]);
          }
     };


     _serial_port.async_read_some(asio::buffer(buffer), read_handler);  
}
