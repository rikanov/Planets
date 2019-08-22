cmake_minimum_required(VERSION 3.0)

project(planets)

add_executable(planets main.cpp)

install(TARGETS planets RUNTIME DESTINATION bin)
