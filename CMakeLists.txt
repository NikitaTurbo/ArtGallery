# CMake config
cmake_minimum_required(VERSION 3.10)
project(AGP) # Art Gallery Problem

# Set project directories
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${PROJECT_ROOT}/include)
set(LIB_DIR ${PROJECT_ROOT}/lib)
set(SRC_DIR ${PROJECT_ROOT}/src)

# Include directories
include_directories(
	${INCLUDE_DIR}
	${LIB_DIR}
)

# Link directories
link_directories(
	${LIB_DIR}/SFML
	${LIB_DIR}/boost
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