#pragma once
#include <cstdint>

namespace lidar::data{
     using namespace std;

     //expects angle in radians
     struct Point2D{
          double x;
          double y;
          float angle;
          uint16_t distance;
          uint8_t intensity;
          uint64_t time_stamp; // in nanoseconds

          Point2D(double x, double y, uint8_t intensity, uint64_t stamp);
          Point2D(float angle, uint16_t distance, uint8_t intensity, uint64_t stamp);
          Point2D(double x, double y, float angle, uint16_t distance, uint8_t intensity, uint64_t stamp);
     };



 
}

