#pragma once
#include <atomic>
#include <stdio.h>  

class FileStream{
     FileStream(const char* path);
     FileStream(FILE* stream);

     ssize_t read(uint8_t *buffer, size_t size);

     bool write(const uint8_t* buffer, size_t size);
     
     void close();
     
     bool is_opened() const;
     
     ~FileStream();
     
     private:
          FILE* _stream;
          std::atomic_bool _is_opened;
};