cmake_minimum_required(VERSION 3.5.1)
include(generate_vs_filters)
include(glob_cxx_sources)
include(cxx_version)

set(target_name WinWrappers)
set(${target_name} true CACHE BOOL "Win32 API calls wrappers")
if(NOT ${${target_name}})
    return()
endif()
add_library(${target_name} INTERFACE)
target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Utility project to see files in ide solution explorer
glob_cxx_sources(${CMAKE_CURRENT_SOURCE_DIR}/include target_sources)
add_custom_target("${target_name}View" SOURCES ${target_sources})
generate_vs_filters(${target_sources})
