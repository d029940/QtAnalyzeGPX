project(GarminGPX_Lib VERSION 0.1
    DESCRIPTION "Garmin GPX Lib)"
    LANGUAGES CXX)


####################################################
# GPX lib

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Xml)

# Alternative: https://pugixml.org, C++ string, filesystem fstream


add_library(garmin_gpx STATIC
  garmingpxfile.cpp
  garmingpxfile.h
)
target_link_libraries(garmin_gpx PRIVATE Qt6::Xml)
target_include_directories(garmin_gpx INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

####################################################
# Garmin Location lib

# Because of QDebug
find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(garmin_drive_loc STATIC
  garmintreenode.cpp
  garmintreenode.h
)
target_link_libraries(garmin_drive_loc PRIVATE Qt6::Core)
target_include_directories(garmin_drive_loc INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
