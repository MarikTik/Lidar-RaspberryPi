cmake_minimum_required(VERSION 3.22.1)
 
project(lidar)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} src/main.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
                        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
                        -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation
                        -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference
                        -Wuseless-cast -Wdouble-promotion -Wformat=2 -Werror)
endif()
