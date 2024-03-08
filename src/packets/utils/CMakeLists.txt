add_library(PACKETS_UTILS STATIC
     streams/file.cpp
     streams/serial.cpp
)


target_include_directories(PACKETS_UTILS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})