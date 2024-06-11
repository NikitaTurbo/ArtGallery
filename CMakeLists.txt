cmake_minimum_required(VERSION 3.5)
project(artGallery)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fsanitize=address -g")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SOURCE_FILES
    sources/components/point/point.cpp
    sources/components/edge/edge.cpp
    sources/components/mpolygon/mpolygon.cpp
    sources/components/guard/guard.cpp
    sources/components/team/team.cpp
    sources/components/visualize/paper/paper.cpp
    sources/components/genetic_algorithm/genetic_algorithm.cpp
    sources/artGallery.cpp
)

find_package(SFML COMPONENTS graphics REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(artGallery ${SOURCE_FILES})
target_link_libraries(artGallery PRIVATE -lsfml-graphics -lsfml-window -lsfml-system)