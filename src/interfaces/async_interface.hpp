#pragma once
#include <boost/asio/io_context.hpp>
#include <vector>


template<typename InterfaceImpl>
struct ConnectionSettings
{
};

template<typename InterfaceImpl>
class AsyncInterface : protected ConnectionSettings<InterfaceImpl> {
public:
     AsyncInterface(boost::asio::io_context& io_context)
          : _io_context(io_context){
           
     }
     template<typename... Args>
     bool open(Args&&... args){
          return static_cast<InterfaceImpl*>(this)->open(std::forward<Args>(args)...);
     }
     void close(){
          static_cast<InterfaceImpl*>(this)->close();
     }
     bool is_open() const{
          return static_cast<InterfaceImpl*>(this)->is_open();
     }
     template<typename Data>
     std::vector<Data> async_read() const{
          return static_cast<InterfaceImpl*>(this)->async_read();
     }
     void async_scan(){
          static_cast<InterfaceImpl*>(this)->async_scan();
     }
     ~AsyncInterface(){
          close();
     }
     constexpr void set_connection_settings(ConnectionSettings<InterfaceImpl>& settings){
          _connection_settings = settings;
     }
protected:
     boost::asio::io_context& _io_context;
     ConnectionSettings<InterfaceImpl> _connection_settings;
};
