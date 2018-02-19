cmake_minimum_required(VERSION 3.8)
project(converter)

set(CMAKE_CXX_STANDARD 11)

# vtk
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(SOURCE_FILES main.cpp)
add_executable(converter ${SOURCE_FILES})
target_link_libraries(converter ${VTK_LIBRARIES})