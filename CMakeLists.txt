cmake_minimum_required(VERSION 3.20)
project(NMLA_Lab_1)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#find_package(Eigen3 3.3)

add_library(lobaev_math Matrix.cpp)

add_executable(main.cpp main.cpp)
#target_link_libraries(main.cpp Eigen3::Eigen)

add_executable(tests.cpp tests.cpp)
target_link_libraries(tests.cpp gtest gtest_main)
