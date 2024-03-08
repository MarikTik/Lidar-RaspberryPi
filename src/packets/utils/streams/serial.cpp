#include "serial.h"

bool Serial::open(const char* port, uint32_t baud_rate){
     _serial_port = ::open(port, O_RDWR | O_NOCTTY | O_NONBLOCK); 

     if (_serial_port < 0) {
        fprintf(stderr, "Error %i from open: %s\n", errno, strerror(errno));
        return false;
     }

     struct internals::termios2 tty;
     if(ioctl(_serial_port, _IOC(_IOC_READ, 'T', 0x2A, sizeof(tty)), &tty)) {
        fprintf(stderr, "Error %i from TCGETS2: %s\n", errno, strerror(errno));
        return false;
     }


     tty.c_cflag |= static_cast<tcflag_t>(CLOCAL | CREAD | CS8);
     tty.c_cflag &= static_cast<tcflag_t>(~(CSTOPB | PARENB));
     tty.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ISIG | IEXTEN));  //|ECHOPRT
     tty.c_oflag &= static_cast<tcflag_t>(~(OPOST));
     tty.c_iflag &= static_cast<tcflag_t>(~(IXON | IXOFF | INLCR | IGNCR | ICRNL | IGNBRK));
     tty.c_cflag &= static_cast<tcflag_t>(~CBAUD);
     tty.c_cflag |= static_cast<tcflag_t>(BOTHER);

     tty.c_ispeed = static_cast<speed_t>(baud_rate);
     tty.c_ospeed = static_cast<speed_t>(baud_rate);

     tty.c_cc[VMIN] = 1; // changed from 0
     tty.c_cc[VTIME] = 0; 

     if(ioctl(_serial_port, _IOC(_IOC_WRITE, 'T', 0x2B, sizeof(tty)), &tty) != 0) {
        fprintf(stderr, "Error %i from TCSETS2: %s\n", errno, strerror(errno));
        return false;
     }

     if (ioctl(_serial_port, _IOC(_IOC_READ, 'T', 0x2A, sizeof(tty)), &tty)) {
        fprintf(stderr, "Error %i from TCGETS2: %s\n", errno, strerror(errno));
        ::close(_serial_port);
        return false;
     }

     tcflush(_serial_port, TCIFLUSH);
     _is_opened.store(true);

     return true;
}

ssize_t Serial::read(uint8_t *buffer, size_t size)
{
     if (!_is_opened.load()) {    
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

bool Serial::write(const uint8_t *buffer, size_t size)
{ 
     if (!_is_opened.load()) {    
        fputs("Error, serial port is not opened\n", stderr);
        return false; 
     }
     ssize_t written = ::write(_serial_port, buffer, size);
     return written == size;     
}

void Serial::close(){
     if (_is_opened.load()){
          _is_opened.store(false);
          ::close(_serial_port);
     }       
}