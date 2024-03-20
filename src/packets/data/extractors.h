#pragma once
#include "point2d.h"
#include <array>

namespace lidar::data{
     

     template<typename N>
     std::array<Point2D, N> extract_from(const stl::Packet<12> &packet);
    
}

