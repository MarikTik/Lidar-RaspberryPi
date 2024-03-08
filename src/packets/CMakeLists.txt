add_subdirectory(utils)
add_subdirectory(data)

target_link_libraries(${PROJECT_NAME} PRIVATE PACKETS_UTILS)
target_link_libraries(${PROJECT_NAME} PRIVATE PACKETS_DATA)