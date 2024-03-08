#include "serial.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <errno.h>
#include <string.h>

SerialStream::SerialStream()
     : _serial_port(-1), _is_opened(false)
{
}

bool SerialStream::open(const char *port, uint32_t baud_rate)
{
     if (is_opened()){
          fprintf(stderr, "Warning, serial port is already opened.\nclosing stream and opening new one\n");
          this->close();
     }

     _serial_port = ::open(port, O_RDWR | O_NOCTTY | O_NONBLOCK); 

     if (_serial_port < 0) {
        fprintf(stderr, "Error %i from open: %s\n", errno, strerror(errno));
        return false;
     }

     struct internals::termios2 options;
     if(ioctl(_serial_port, _IOC(_IOC_READ, 'T', 0x2A, sizeof(options)), &options)) {
        fprintf(stderr, "Error %i from TCGETS2: %s\n", errno, strerror(errno));
        return false;
     }


     options.c_cflag |= static_cast<tcflag_t>(CLOCAL | CREAD | CS8);
     options.c_cflag &= static_cast<tcflag_t>(~(CSTOPB | PARENB));
     options.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ISIG | IEXTEN));  //|ECHOPRT
     options.c_oflag &= static_cast<tcflag_t>(~(OPOST));
     options.c_iflag &= static_cast<tcflag_t>(~(IXON | IXOFF | INLCR | IGNCR | ICRNL | IGNBRK));
     options.c_cflag &= static_cast<tcflag_t>(~CBAUD);
     options.c_cflag |= static_cast<tcflag_t>(BOTHER);

     options.c_ispeed = static_cast<speed_t>(baud_rate);
     options.c_ospeed = static_cast<speed_t>(baud_rate);

     options.c_cc[VMIN] = 1; // changed from 0
     options.c_cc[VTIME] = 0; 

    
     if(ioctl(_serial_port, _IOC(_IOC_WRITE, 'T', 0x2B, sizeof(options)), &options) != 0) {
        fprintf(stderr, "Error %i from TCSETS2: %s\n", errno, strerror(errno));
        this->close();
        return false;
     }

     if (ioctl(_serial_port, _IOC(_IOC_READ, 'T', 0x2A, sizeof(options)), &options)) {
        fprintf(stderr, "Error %i from TCGETS2: %s\n", errno, strerror(errno));
        this->close();
        return false;
     }

     tcflush(_serial_port, TCIFLUSH);
     _is_opened.store(true);

     return true;
}

ssize_t SerialStream::read(uint8_t *buffer, size_t size)
{
     if (!is_opened()) {    
        fputs("Error, serial port is not opened\n", stderr);
        return -1; 
     }
     ssize_t total_received = 0; 
     ssize_t received = -1;

     fd_set read_fds;
     static constexpr timespec timeout = {0, static_cast<long>(100 * 1e6)};
     int select_status = -1;
     while (total_received < size and received and select_status) {

          FD_ZERO(&read_fds);
          FD_SET(_serial_port, &read_fds);
          select_status = pselect(_serial_port + 1, &read_fds, NULL, NULL, &timeout, NULL);
          if (select_status < 0) {
            if (errno == EINTR) continue; // Interrupted, try again
            fprintf(stderr, "Error %i from pselect: %s\n", errno, strerror(errno));
            return -1;
          } 
          if (FD_ISSET(_serial_port, &read_fds)) {
            received = ::read(_serial_port, buffer + total_received, size - total_received);
            if (received < 0) {
               fprintf(stderr, "Error %i from read: %s\n", errno, strerror(errno));
               return -1;
            } 
            total_received += received;
          }
     }
     return total_received;
}

bool SerialStream::write(const uint8_t *buffer, size_t size)
{ 
     if (!is_opened()) {    
        fputs("Error, serial port is not opened\n", stderr);
        return false; 
     }
     ssize_t written = ::write(_serial_port, buffer, size);
     return written == size;     
}

void SerialStream::close(){
     if (is_opened()){
          this->_is_opened.store(false);
          ::close(_serial_port);
     }       
}

bool SerialStream::is_opened() const
{
     return _is_opened.load();
}

SerialStream::~SerialStream()
{
     this->close();
}
