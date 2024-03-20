#pragma once
#include "data.hpp"
#include <array>

namespace lidar::data{
     
     template<typename N>
     std::array<stl::Point, N> extract_from(const stl::Packet<N> &packet);
    
}

