add_library(PACKETS_DATA STATIC
     point2d.cpp
     extractors.cpp
)

target_include_directories(PACKETS_DATA PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})