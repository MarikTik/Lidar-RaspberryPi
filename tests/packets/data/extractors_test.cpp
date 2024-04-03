#define BOOST_TEST_MODULE ExtractorsTest
#include <boost/test/unit_test.hpp>
#include "../src/packets/data/extractors.hpp"




BOOST_AUTO_TEST_CASE(ExtractStlPacket)
{
     using namespace lidar::transmission;
 
     std::array<uint8_t, 47> valid_packet_raw = {0x54, 0x2C, 0x68, 0x08, 0xAB, 0x7E, 0xE0, 0x00, 0xE4, 0xDC, 0x00, 0xE2, 0xD9, 0x00, 0xE5, 0xD5, 0x00, 0xE3, 0xD3, 0x00, 0xE4, 0xD0, 0x00, 0xE9, 0xCD, 0x00, 0xE4, 0xCA, 0x00, 0xE2, 0xC7, 0x00, 0xE9, 0xC5, 0x00, 0xE5, 0xC2, 0x00, 0xE5, 0xC0, 0x00, 0xE5, 0xBE, 0x82, 0x3A, 0x1A, 0x50};

     const auto packet = PacketBase<stl::Packet<12>>::create(valid_packet_raw.cbegin(), valid_packet_raw.cend());
     const auto [points, supplied_data] = lidar::data::extract_from(packet);

     constexpr float angular_uncertainty = .5f; // % uncertainty
     constexpr float distance_uncertainty = .01f; // % uncertainty
     // test supplied data
     BOOST_CHECK_CLOSE(supplied_data.angular_speed, 37.56, angular_uncertainty);
     BOOST_CHECK_EQUAL(supplied_data.timestamp, 0x1a3a);

     // test points
     BOOST_CHECK_CLOSE(points[0].distance, 2.24, distance_uncertainty);
     BOOST_CHECK_CLOSE(points[0].angle, 5.65, angular_uncertainty);
     BOOST_CHECK_EQUAL(points[0].intensity, 228);

     BOOST_CHECK_CLOSE(points[1].distance, 2.2, distance_uncertainty);
     BOOST_CHECK_CLOSE(points[1].angle, 5.67, angular_uncertainty);
     BOOST_CHECK_EQUAL(points[1].intensity, 0xe2);
     
    
     BOOST_CHECK_CLOSE(points[2].angle, 5.69, angular_uncertainty);
      
     BOOST_CHECK_CLOSE(points[11].distance, 1.92, distance_uncertainty);
     BOOST_CHECK_CLOSE(points[11].angle, 5.84, angular_uncertainty);
     BOOST_CHECK_EQUAL(points[11].intensity, 0xe5);

}


