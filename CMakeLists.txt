cmake_minimum_required(VERSION 3.0)

project(planets)

include_directories(inc/)

add_executable(planets main.cpp
                                src/str_node.cpp
                                src/stone.cpp
                                src/step.cpp 
                                src/result.cpp
                                src/sstack.cpp
                                src/datacache.cpp
                                src/collection.cpp
                                src/board.cpp 
                                src/generator.cpp
                                src/cache.cpp
                                src/minimaxoptimizer.cpp
                                src/engine.cpp
                                src/basicui.cpp
                                src/view2d.cpp
                                )

install(TARGETS planets RUNTIME DESTINATION bin)
