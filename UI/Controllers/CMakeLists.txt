set(SRC actions.cpp
        "${CMAKE_CURRENT_SOURCE_DIR}/actions.h"
)

# Because of QDebug
#find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(controller OBJECT ${SRC})
#target_link_libraries(controller PRIVATE Qt6::Core)
target_include_directories(controller INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
