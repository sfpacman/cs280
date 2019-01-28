cmake_minimum_required(VERSION 3.13)
project(cs280)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(cs280
        Count3sProcessSerial
        Count3sProcessSerial.cpp
        threesData.bin)
