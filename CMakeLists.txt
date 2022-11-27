cmake_minimum_required(VERSION 3.16...3.24)

project(AnalyzeGPX
  VERSION 0.1
   DESCRIPTION "Analyze Garmin GPX files stored in a Garmin folder"
   LANGUAGES CXX)

set(EXECUTABLE_NAME ${PROJECT_NAME})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Garmin GPX Lib:
 set(GARMIN_LIB garmin)
 add_subdirectory(GarminGpxLib)

# Gui - QtWidgets
add_subdirectory(UI/Widgets)

# Sources for the the models
add_subdirectory(Models)




