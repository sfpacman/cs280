cmake_minimum_required(VERSION 3.13)
project(cs280)

set(CMAKE_CXX_STANDARD 14)
find_library(  libpthread, /lib/x86_64-linux-gnu/libpthread.so.0)
link_libraries(  libpthread)
include_directories(/lib/x86_64-linux-gnu/)
link_directories(/lib/x86_64-linux-gnu/)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(Threads)
include_directories(.)

add_executable(cs280
        threesData.bin
        Count3sThreadParallel.cpp)

target_link_libraries(cs280 Threads)