find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
# find_package(Boost CONFIG COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE TEST_SOURCES "*_test.cpp")

foreach(TEST_SOURCE ${TEST_SOURCES})
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME} ${Boost_LIBRARIES})
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()