cmake_minimum_required(VERSION 2.8) 
PROJECT (bsnake_lane_detection)

add_definitions ("-w")
find_package(OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set( NAME_SRC
    src/main.cpp
    src/laneSegmentor.cpp
)

set( NAME_HEADERS
	include/laneSegmentor.hpp
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

add_executable(road_seg src/main.cpp src/roadSegmentor.cpp)
target_link_libraries(road_seg ${OpenCV_LIBRARIES})