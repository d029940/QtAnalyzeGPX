cmake_minimum_required(VERSION 3.16)

project(
  AnalyzeGPX_QML
  VERSION 0.1
  DESCRIPTION "Analyze Garmin GPX files stored in a Garmin folder"
  LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
  Qt6
  COMPONENTS Quick
  REQUIRED)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} main.cpp controllers/controller.cpp
                  controllers/controller.h)

qt_add_qml_module(
  ${PROJECT_NAME}
  URI
  AnalyzeGPX
  VERSION
  1.0
  QML_FILES
  MainView.qml
  RteTrkWptListView.qml
  ListHeader.qml
  DevicesTreeView.qml)

print(APP_RESOUCRE_DIR)
# Windows app icon
set(app_icon_win "${APP_RESOUCRE_DIR}/win.rc")
print(app_icon_win)

# Licenses of the app
set(licenses "${APP_RESOUCRE_DIR}/Licenses/01_License_BSD-4.txt")

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES MACOSX_BUNDLE_GUI_IDENTIFIER analyze.manfredkern.com
             MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
             MACOSX_BUNDLE_SHORT_VERSION_STRING
             ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
             MACOSX_BUNDLE TRUE
             WIN32_EXECUTABLE TRUE)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Quick model garmin_drive_loc
                                              garmin_gpx garmin_fit)

install(
  TARGETS ${PROJECT_NAME}
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

qt_generate_deploy_app_script(TARGET ${PROJECT_NAME} OUTPUT_SCRIPT
                              deploy_script NO_UNSUPPORTED_PLATFORM_ERROR)
install(SCRIPT ${deploy_script})
