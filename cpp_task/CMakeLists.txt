cmake_minimum_required(VERSION 3.15)
project(cpp_task)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost REQUIRED COMPONENTS date_time)

add_executable(cpp_task main.cpp DbValue.cpp DbValue.hpp)

target_link_libraries(cpp_task PUBLIC Boost::date_time)