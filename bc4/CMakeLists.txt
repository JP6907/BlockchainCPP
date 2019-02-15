cmake_minimum_required(VERSION 3.12)
project(BC4)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. DIR_SRCS)

add_executable(BC4 main.cpp ${DIR_SRCS} ../utils/sha256.cpp)
