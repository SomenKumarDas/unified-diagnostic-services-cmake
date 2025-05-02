cmake_minimum_required(VERSION 3.10)

project(uds_cmake VERSION 0.1 LANGUAGES C)

add_executable(uds_cmake main.c)

# Include the Dcm module
add_subdirectory(components/Dcm)

# Link the Dcm module with the main executable
target_link_libraries(uds_cmake PRIVATE Dcm)

# Include directories for the main executable
target_include_directories(uds_cmake PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)