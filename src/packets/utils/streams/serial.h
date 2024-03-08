#include <atomic>
#include <stdint.h>
#include <unistd.h>
namespace internals{
     #include <linux/termios.h>
}

class SerialStream{
public:
     SerialStream();

     bool open(const char* port, uint32_t baud_rate);

     ssize_t read(uint8_t *buffer, size_t size);

     bool write(const uint8_t* buffer, size_t size);
     
     void close();
     
     
     ~SerialStream();
     
     private:
          int _serial_port;
          std::atomic_bool _is_opened;
};