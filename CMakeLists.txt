cmake_minimum_required(VERSION 2.8)
project(Simulation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Simulation main.cpp Counter.cpp Counter.h Passenger.cpp Passenger.h Event.cpp Event.h Action.cpp Action.h)