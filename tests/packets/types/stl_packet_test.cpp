#define BOOST_TEST_MODULE StlPacketTest 
#include "../src/packets/types/stl_packet.hpp"
#include "../src/packets/types/packet_base.hpp"
#include <boost/test/unit_test.hpp>
#include <array>

using namespace lidar::transmission;
std::array<uint8_t, 47> valid_packet_raw = {0x54, 0x2C, 0x68, 0x08, 0xAB, 0x7E, 0xE0, 0x00, 0xE4, 0xDC, 0x00, 0xE2, 0xD9, 0x00, 0xE5, 0xD5, 0x00, 0xE3, 0xD3, 0x00, 0xE4, 0xD0, 0x00, 0xE9, 0xCD, 0x00, 0xE4, 0xCA, 0x00, 0xE2, 0xC7, 0x00, 0xE9, 0xC5, 0x00, 0xE5, 0xC2, 0x00, 0xE5, 0xC0, 0x00, 0xE5, 0xBE, 0x82, 0x3A, 0x1A, 0x50};


BOOST_AUTO_TEST_CASE(StlPacketUidTest){
    auto stl_packet = stl::Packet<12>{};
    BOOST_CHECK_EQUAL(stl_packet.uid(), 0x542C);
}

BOOST_AUTO_TEST_CASE(StlPacketCreateTest){
     auto packet = PacketBase<stl::Packet<12>>::create(valid_packet_raw.cbegin(), valid_packet_raw.cend());
     BOOST_CHECK_EQUAL(packet.header, 0x54);
     BOOST_CHECK_EQUAL(packet.ver_len, 0x2C);
     BOOST_CHECK_EQUAL(packet.speed, 2152);
     BOOST_CHECK_EQUAL(packet.start_angle, 32427);
     BOOST_CHECK_EQUAL(packet.points[0].distance, 224);
     BOOST_CHECK_EQUAL(packet.points[0].intensity, 228);
     BOOST_CHECK_EQUAL(packet.points[1].distance, 220);
     BOOST_CHECK_EQUAL(packet.points[1].intensity, 0xe2);
     BOOST_CHECK_EQUAL(packet.points[11].distance, 0xc0);
     BOOST_CHECK_EQUAL(packet.points[11].intensity, 0xe5);
     BOOST_CHECK_EQUAL(packet.end_angle, 33470);
}

BOOST_AUTO_TEST_CASE(StlPacketIsValid)
{
     auto packet = PacketBase<stl::Packet<12>>::create(valid_packet_raw.cbegin(), valid_packet_raw.cend());
     BOOST_CHECK_EQUAL(packet.is_valid(), true);
}