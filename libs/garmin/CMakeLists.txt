cmake_minimum_required(VERSION 3.29)
project(
  GarminGPX_Lib
  VERSION 0.1
  DESCRIPTION "Garmin GPX Lib)"
  LANGUAGES CXX)

# ##############################################################################
# GPX lib

find_package(Qt6 REQUIRED COMPONENTS Xml)

# find_package(QT NAMES Qt6 REQUIRED COMPONENTS Xml) find_package(Qt6 REQUIRED
# COMPONENTS Xml)

# Alternative: https://pugixml.org, C++ string, filesystem fstream

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a" “.so”)
add_library(garmin_gpx STATIC garmingpxfile.cpp garmingpxfile.h)
target_link_libraries(garmin_gpx PRIVATE Qt6::Xml)
target_include_directories(garmin_gpx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ##############################################################################
# Garmin FIT lib

add_library(garmin_fit STATIC garminfitfile.h garminfitfile.cpp)
target_link_libraries(garmin_fit PRIVATE Qt6::Core)
target_include_directories(garmin_fit PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ##############################################################################
# Garmin Location lib

# Because of QDebug
find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(garmin_drive_loc STATIC garmintreenode.cpp garmintreenode.h
                                    garminfiles.h garminfiles.cpp)
target_link_libraries(garmin_drive_loc PRIVATE Qt6::Core)
target_include_directories(garmin_drive_loc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
