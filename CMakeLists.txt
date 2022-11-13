cmake_minimum_required(VERSION 3.7)

project(planets)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/" )

# the source of FindSDL2_image.cmake can be found: https://github.com/trenki2/SDL2Test
find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(inc/)

add_compile_options( -lSDL2 -lSDL2_image )
add_executable(planets main.cpp
                                src/str_node.cpp
                                src/stone.cpp
                                src/step.cpp 
                                src/sstack.cpp
                                src/collection.cpp
                                src/board.cpp 
                                src/generator.cpp
                                src/cache.cpp
                                src/engine.cpp
                                src/basicui.cpp
                                src/view2d.cpp
                                )
target_link_libraries(planets ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} )
install(TARGETS planets RUNTIME DESTINATION bin)
