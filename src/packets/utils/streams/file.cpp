#include "file.h"

 

FileStream::FileStream(const char *path)
     : _stream(fopen(path, "rb")),
      _is_opened(_stream != nullptr)
{
}

FileStream::FileStream(FILE *stream)
     : _stream(stream),
      _is_opened(true)
{
}


ssize_t FileStream::read(uint8_t *buffer, size_t size)
{
     return ssize_t();
}

bool FileStream::write(const uint8_t *buffer, size_t size)
{
     return false;
}

void FileStream::close()
{
}

bool FileStream::is_opened() const
{
     return false;
}

FileStream::~FileStream()
{
}
