cmake_minimum_required(VERSION 3.16...3.24)

project(
  AnalyzeGPX
  VERSION 0.1
  DESCRIPTION "Analyze Garmin GPX files stored in a Garmin folder"
  LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})
# To change the values of CMAKE_INSTALL_BINDIR or CMAKE_INSTALL_LIBDIR, set the
# variables before the Qt6Core package is found.

# Show QtCreator non build files
add_custom_target(info SOURCES README.md LICENSE.md TODO.txt)

# ##############################################################################
# Some helper functions

# print all the arguments given
function(print)
  foreach(var ${ARGN})
    message("${var} = ${${var}}")
  endforeach()
endfunction()

# print environment
function(print_env)
  foreach(var ${ARGN})
    message("${var} = $ENV{${var}}")
  endforeach()
endfunction()

# ##############################################################################
# build related commands

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Xml)

# Resources
set(APP_RESOUCRE_DIR "${PROJECT_SOURCE_DIR}/resources")
add_subdirectory(resources)

# add general utilities
set(LICENSES_LIB licenses)
add_subdirectory(utils)

# Garmin GPX & Drive Location libs:
add_subdirectory(libs/garmin)

# Drive / Volume info
add_subdirectory(libs/volumeInfo)

# Sources for the the models
add_subdirectory(models)

# Gui - QtWidgets
add_subdirectory(apps/Widgets)

# Gui - QML
add_subdirectory(apps/QML)
