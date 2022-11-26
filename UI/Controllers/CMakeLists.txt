set(CMAKE_AUTOMOC ON)

set(SRC actions.cpp
        "${CMAKE_CURRENT_SOURCE_DIR}/actions.h"
)


find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(controller OBJECT ${SRC})
target_link_libraries(controller PRIVATE Qt6::Widgets)
target_include_directories(controller INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
