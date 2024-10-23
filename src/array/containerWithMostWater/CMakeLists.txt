cmake_minimum_required(VERSION 3.10)

# Get the name of the current folder
get_filename_component(CURRENT_FOLDER ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Print the current folder name
message("Configuring: ${CURRENT_FOLDER}")

# Set the project name
project(${CURRENT_FOLDER})

# Specify the source files
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/containerWithMostWater.cpp)

message(STATUS "Source files: ${SOURCE_FILES}")

# Add the executable
add_executable(${CURRENT_FOLDER} ${SOURCE_FILES})

target_link_libraries(${CURRENT_FOLDER} PUBLIC utils)

cmake_path(RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR BASE_DIRECTORY ${CMAKE_SOURCE_DIR} OUTPUT_VARIABLE SOURCE_RELATIVE_PATH)

# Set the output directory
set_target_properties(${CURRENT_FOLDER} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${SOURCE_RELATIVE_PATH}
)