cmake_minimum_required(VERSION 3.14)

project(
  volumeInfo
  VERSION 0.1
  DESCRIPTION "Volume / Drive info lib"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(volumeInfo STATIC volumeinfo.cpp volumeinfo.h)

target_link_libraries(volumeInfo PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_include_directories(volumeInfo INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(volumeInfo PRIVATE VOLUMEINFO_LIBRARY)
