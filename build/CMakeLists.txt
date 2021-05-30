cmake_minimum_required(VERSION 3.10)

project(diffmatrix VERSION 1.2)

#add a configure_file

include_directories(${CMAKE_SOURCE_DIR}/../external/ncl ${CMAKE_SOURCE_DIR}/../external/ncl/ncl)
if (MSVC)
    include_directories(${CMAKE_SOURCE_DIR}/../wineditline/include)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakemodules")
set(PATH_LIB_NCL "ncl_static")

if(MSVC)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x -O3")
endif()
set(CMAKE_INTSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../install")
add_subdirectory(${CMAKE_SOURCE_DIR}/../external/ncl ${CMAKE_CURRENT_BINARY_DIR}/external/ncl)
add_subdirectory(${CMAKE_SOURCE_DIR}/../diffmatrix ${CMAKE_CURRENT_BINARY_DIR}/diffmatrix)
