# Here go the abstract item models

find_package(Qt6 REQUIRED COMPONENTS Core)
qt_standard_project_setup()


add_library(model OBJECT
  garmintreemodel.cpp
  garmintreemodel.h
  gpxtablemodel.cpp
  gpxtablemodel.h
)

target_link_libraries(model PUBLIC garmin_drive_loc garmin_gpx Qt6::Core)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
