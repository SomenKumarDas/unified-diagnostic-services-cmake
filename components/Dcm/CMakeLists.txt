# Add the Dcm module as a library
file(GLOB DCM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

file(GLOB DCM_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h
)

add_library(Dcm STATIC ${DCM_SOURCES})

# Include the Dcm module's headers
target_include_directories(Dcm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)