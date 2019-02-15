cmake_minimum_required(VERSION 3.12)
project(Test_sha256)

set(CMAKE_CXX_STANDARD 14)

add_executable(Test_sha256 test_sha256.cpp sha256.cpp)
