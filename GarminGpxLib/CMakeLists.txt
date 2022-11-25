project(GarminGPX_Lib VERSION 0.1
    DESCRIPTION "Garmin GPX Lib)"
    LANGUAGES CXX)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Xml)

# Alternative: https://pugixml.org, C++ string, filesystem fstream


set(SOURCES
    garmingpxfile.cpp
    garmingpxfile.h
)

add_library(${GARMIN_LIB} STATIC ${SOURCES})
target_link_libraries(${GARMIN_LIB} PRIVATE Qt6::Xml)
target_include_directories(${GARMIN_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
