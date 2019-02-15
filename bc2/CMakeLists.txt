cmake_minimum_required(VERSION 3.12)
project(BC2)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

aux_source_directory(source DIR_SRCS)

add_executable(BC2 main.cpp ${DIR_SRCS} ../utils/sha256.cpp)
