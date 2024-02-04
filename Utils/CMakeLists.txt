project(licenses VERSION 0.1
    DESCRIPTION "Find Liceneses for project)"
    LANGUAGES CXX)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

set(SOURCES
    licenses.cpp
    licenses.h
    resoucehandling.cpp
    resoucehandling.h
)

add_library(${LICENSES_LIB} STATIC ${SOURCES})
target_link_libraries(${LICENSES_LIB} PRIVATE Qt6::Core)
target_include_directories(${LICENSES_LIB} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
