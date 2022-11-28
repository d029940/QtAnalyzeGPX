cmake_minimum_required(VERSION 3.16...3.24)

project(AnalyzeGPX
  VERSION 0.1
   DESCRIPTION "Analyze Garmin GPX files stored in a Garmin folder"
   LANGUAGES CXX)

set(EXECUTABLE_NAME ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Porject source dir: " ${PROJECT_SOURCE_DIR})

# Garmin GPX Lib:
 set(GARMIN_LIB garmin)
 add_subdirectory(libs)

# Gui - QtWidgets
add_subdirectory(apps/Widgets)

# Sources for the the models
add_subdirectory(models)


# Resources
set(RESOURCE_DIR "")
add_subdirectory(resources)
