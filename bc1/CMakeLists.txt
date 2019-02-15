cmake_minimum_required(VERSION 3.12)
project(BC1)

set(CMAKE_CXX_STANDARD 14)

add_executable(BC1 main.cpp Block.cpp Blockchain.cpp ../utils/sha256.cpp)
