cmake_minimum_required(VERSION 3.16...3.24)

project(AnalyzeGPX
  VERSION 0.1
   DESCRIPTION "Analyze Garmin GPX files stored in a Garmin folder"
   LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

# Show QtCreator non build files
add_custom_target(info SOURCES
  README.md ToDo.txt)

####################################################
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

print_env(HOMEBREW_PREFIX)

######################################################
# build related commands

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Resources
set(APP_RESOUCRE_DIR "${PROJECT_SOURCE_DIR}/resources")
add_subdirectory(resources)

# add general utilities
set(LICENSES_LIB licenses)
add_subdirectory(utils)

# Garmin GPX Lib:
 set(GARMIN_LIB garmin)
 add_subdirectory(libs)

# Gui - QtWidgets
add_subdirectory(apps/Widgets)

# Gui - QML
add_subdirectory(apps/QML)

# Sources for the the models
add_subdirectory(models)



