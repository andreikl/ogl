# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (ogl)

find_package(OpenGL REQUIRED)

message( ${CMAKE_SOURCE_DIR} )
message( ${CMAKE_BINARY_DIR} )

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory." )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces." )
endif()

# Compile external dependencies 
add_subdirectory (external)

include_directories(
    external/glfw-3.1.2/include/GLFW/
    external/glew-1.13.0/include/
    external/glm-0.9.7.1/
    include/
    .
)

set(ALL_LIBS
    ${OPENGL_LIBRARY}
    glfw
    GLEW_1130
)

add_definitions(
    -DTW_STATIC
    -DTW_NO_LIB_PRAGMA
    -DTW_NO_DIRECT3D
    -DGLEW_STATIC
    -D_CRT_SECURE_NO_WARNINGS
)

add_executable(ogl 
    src/app.cpp
    src/main.cpp
    src/tutorial1/tutorial1.cpp
)
target_link_libraries(ogl
    ${ALL_LIBS}
)
