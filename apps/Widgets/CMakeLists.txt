cmake_minimum_required(VERSION 3.29)
project(
  AnalyzeGPX_Widgets
  VERSION 0.1
  DESCRIPTION "Analyze Garmin GPX files (Widget Version)"
  LANGUAGES CXX)

configure_file(AnalyzeGPX_Widgets_config.h.in AnalyzeGPX_Widgets_config.h)

set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    controllers/controller.h
    controllers/controller.cpp
    aboutdialog.h
    aboutdialog.cpp
    aboutdialog.ui)

print(APP_RESOUCRE_DIR)
# Windows app icon
set(app_icon_win "${APP_RESOUCRE_DIR}/win.rc")
print(app_icon_win)

# Licenses of the app
set(licenses "${APP_RESOUCRE_DIR}/Licenses/01_License_BSD-4.txt")

# Define executable Windows needs a resource file for the app icon
# https://doc-snapshots.qt.io/qt6-6.4/appicon.html
qt_add_executable(${PROJECT_NAME} MANUAL_FINALIZATION ${PROJECT_SOURCES}
                  ${app_icon_win} ${licenses})

target_include_directories(
  ${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/controllers" include)

print(PROJECT_BINARY_DIR)
target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

target_link_libraries(
  ${PROJECT_NAME} PRIVATE Qt6::Widgets model garmin_drive_loc garmin_gpx
                          garmin_fit ${LICENSES_LIB})

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

install(
  TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION "C:/PortableApps/QtAnalyzeGPX")
# RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

qt_generate_deploy_app_script(TARGET ${PROJECT_NAME} OUTPUT_SCRIPT
                              deploy_script NO_UNSUPPORTED_PLATFORM_ERROR)
install(SCRIPT ${deploy_script})
