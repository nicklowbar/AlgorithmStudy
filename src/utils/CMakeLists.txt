# Get the name of the current folder
get_filename_component(CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} NAME)

message("Configuring: ${CURRENT_FOLDER}")

set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/printHelper.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/logHelper.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/treeNode.cpp
    )

message(STATUS "Source files: ${SOURCE_FILES}")

project(${CURRENT_FOLDER})

add_library(${CURRENT_FOLDER} STATIC ${SOURCE_FILES})
target_include_directories(${CURRENT_FOLDER} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)



