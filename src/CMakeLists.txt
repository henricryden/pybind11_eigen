cmake_minimum_required(VERSION 3.3)
project(EigenExample)

# Options
option(PY_WRAPPERS "Build Python wrappers" ON)

# Extra cmake files
include(CMakePrintHelpers)
include(CMakePythonWrappers.cmake)

set(CMAKE_CXX_STANDARD 14)

find_package(Eigen3 3.3 REQUIRED NO_MODULE) # apt install libeigen3-dev

include_directories(${PROJECT_SOURCE_DIR}/../include)

# Targets
add_subdirectory(recon)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} advancedRecon Eigen3::Eigen)

get_directory_property(include_dirs DIRECTORY ${CMAKE_SOURCE_DIR} INCLUDE_DIRECTORIES)
message("All include directories: ${include_dirs}")
