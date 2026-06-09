# cmake versioning and project setup
cmake_minimum_required(VERSION 3.10)
project(xsef VERSION 0.1.0 LANGUAGES CXX)

# set c++20 as standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include all files from src and include directories
file(GLOB SOURCES "src/*.cc")
file(GLOB NESTEDSOURCES "src/**/*.cc")
file(GLOB HEADERS "include/*.hpp")

# executable based on the sources and headers
add_executable(xsef ${SOURCES} ${NESTEDSOURCES} ${HEADERS})
target_include_directories(xsef PUBLIC "${PROJECT_SOURCE_DIR}/include")