#pragma once
#include "point2d.h"
#include "../types/types.h"
#include <array>

namespace lidar::data{
     using namespace lidar::transmission;

     std::array<Point2D, 12> extract_from(const stl::Packet<12> &packet);
     // add additional extract_from functions here
}

