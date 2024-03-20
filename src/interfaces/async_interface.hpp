#pragma once
#include <boost/asio/io_context.hpp>


template<typename InterfaceImpl>
class AsyncInterface{
public:
     AsyncInterface(boost::asio::io_context& io_context)
          : _io_context(io_context){
           
     }
     bool open(){
          return static_cast<InterfaceImpl*>(this)->open();
     }
     void close(){
          static_cast<InterfaceImpl*>(this)->close();
     }
     bool is_open(){
          return static_cast<InterfaceImpl*>(this)->is_open();
     }
     void async_read(){
          static_cast<InterfaceImpl*>(this)->async_read();
     }
     void async_scan(){
          static_cast<InterfaceImpl*>(this)->async_scan();
     }
     ~AsyncInterface(){
          close();
     }
protected:
     boost::asio::io_context& _io_context;
};
