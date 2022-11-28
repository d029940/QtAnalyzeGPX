message("Resources for " ${EXECUTABLE_NAME})
qt_add_resources(${EXECUTABLE_NAME} "licenses"
  PREFIX "/Licenses"
  FILES
    01_License_BSD-4.txt
    03_License_lgpl-3_0.txt
)
