#pragma once
#include "packets/data.hpp"
#include "packets/packets.hpp"
#include <array>
#include <utility>

namespace lidar::data{
     using namespace lidar;

     template<std::size_t N>
     std::pair<std::array<data::stl::Point, N>, data::stl::Point::SuppliedData>
     extract_from(const transmission::stl::Packet<N> &packet);
}

#include "extractors.tpp"
