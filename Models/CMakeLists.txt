set(SRC garmintreenode.cpp
        "${CMAKE_CURRENT_SOURCE_DIR}/garmintreenode.h"
)

# Because of QDebug
find_package(Qt6 REQUIRED COMPONENTS Core)

add_library(model OBJECT ${SRC})
target_link_libraries(model PRIVATE Qt6::Core)
target_include_directories(model INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

