#cmake_minimum_required(VERSION 3.13)
project(cs280)

set(CMAKE_CXX_STANDARD 14)
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#find_package(Threads REQUIRED)
#find_package(Threads)
include_directories(.)

add_executable(cs280
        threesData.bin
        Count3sIPC.cpp)

#target_link_libraries(cs280 Threads)