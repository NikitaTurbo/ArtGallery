# CMake config
cmake_minimum_required(VERSION 3.10)
project(AGP) # Art Gallery Problem

# Set project directories
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${PROJECT_ROOT}/include)
set(SRC_DIR ${PROJECT_ROOT}/src)

# SFML
set(SFML_INCLUDE_DIR ${PROJECT_ROOT}/lib/SFML/include)
set(SFML_LIB_DIR ${PROJECT_ROOT}/lib/SFML/lib)

# boost
set(BOOST_INCLUDE_DIR ${PROJECT_ROOT}/lib)

# Include directories
include_directories(
	${INCLUDE_DIR}
	${SFML_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
)

# Link directories
link_directories(
	${SFML_LIB_DIR}
)

# Set source files
set(SOURCE_FILES
	# Components (interface & ui)
	${SRC_DIR}/components/interface/point.cpp
	${SRC_DIR}/components/interface/edge.cpp
	${SRC_DIR}/components/interface/mpolygon.cpp
	${SRC_DIR}/components/interface/guard.cpp
	${SRC_DIR}/components/interface/team.cpp
	${SRC_DIR}/components/interface/genetic_algorithm.cpp
	${SRC_DIR}/components/ui/view.cpp
	
	# Application (main)
	${SRC_DIR}/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link libraries to executable
target_link_libraries(${PROJECT_NAME} PRIVATE
	${Boost_LIBRARIES}
	sfml-window
	sfml-graphics
	sfml-system
)