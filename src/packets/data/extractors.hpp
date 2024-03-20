#pragma once
#include "packets/data.hpp"
#include "packets/packets.hpp"
#include <array>

namespace lidar::data{
     using namespace lidar;

     template<std::size_t N>
     std::array<data::stl::Point, N> extract_from(const transmission::stl::Packet<N> &packet);
}

#include "extractors.tpp"
