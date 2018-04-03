cmake_minimum_required(VERSION 3.10)
project(Simulator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pthread")

add_executable(Simulator main.c PBC.c PBC.h PQueue.c PQueue.h Socket.c Socket.h)