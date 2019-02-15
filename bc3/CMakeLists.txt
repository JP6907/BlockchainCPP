cmake_minimum_required(VERSION 3.12)
project(BC3)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. DIR_SRCS)

add_executable(BC3 main.cpp ${DIR_SRCS} ../utils/sha256.cpp)
