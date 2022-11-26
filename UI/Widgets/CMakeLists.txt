project(AnalyzeGPX_Widgets VERSION 0.1
    DESCRIPTION "Analyze Garmin GPX files (Widget Version)"
    LANGUAGES CXX)

configure_file(AnalyzeGPX_Widgets_config.h.in AnalyzeGPX_Widgets_config.h)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${EXECUTABLE_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${EXECUTABLE_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${EXECUTABLE_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${EXECUTABLE_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_directories(${EXECUTABLE_NAME} PUBLIC ${PROJECT_BINARY_DIR})

target_link_libraries(${EXECUTABLE_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets model controller)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER analyze.manfredkern.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ${EXECUTABLE_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${EXECUTABLE_NAME})
endif()
