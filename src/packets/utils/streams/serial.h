#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <atomic>
namespace internals{
     #include <linux/termios.h>
}
#include <errno.h>
#include <string.h>
#include <stdint.h>


class Serial{
public:
     bool open(const char* port, uint32_t baud_rate);

     ssize_t read(uint8_t *buffer, size_t size);

     bool write(const uint8_t* buffer, size_t size);
     
     void close();

     ~Serial();
     
     private:
          int _serial_port;
          std::atomic_bool _is_opened;
};